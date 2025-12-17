#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
#
# $0 : maddr2line.sh is a Linux Host based script that resolves a single iteration MLT log 
# instruction pointer addresses of unidentified file/line# records.

# Output:

# Variables:
NO_FILE_LINENUM_STR="(null):0"
ELF_START_STR="::"
ELF_END_STR=""

ELF_PROPS_DBG_SYM="debug symbols"
ELF_PROPS_NOT_STR="not stripped"
ELF_PROPS_STRIPPED="stripped"
ELF_PROPS_NOT_EXIST="doesn't exist"

ELF_PSEC_STARTOF_TEXT="<start_of_exec_secs>"
ELF_PSEC_ENDOF_TEXT="<end_of_exec_secs>"

# Function: usage
function usage()
{
	echo "$name# Usage : `basename $0 .sh` [-r folder -m /proc/<pid>/maps [-l mltlog | -d iplist | -a file/addr ]] | [-h]"
	echo "$name# Instruction ponter address to line converter"
	echo "$name# -r    : a rootFS folder"
	echo "$name# -maps : a /proc/<pid>/maps file of a process"
	echo "$name# -mlt  : a single iteration MLT log of a process: mutually exclusive with -a"
	echo "$name# -mafs : a single iteration MAFS log of a process: mutually exclusive with -a and -mafs"
	echo "$name# -a    : 2 mode support: 1) an instruction pointer hex address; 2) a one column file with a list of ip hex addresses : mutually exclusive with -l & -d"
	echo "$name# -d    : a file list descriptor of files containing a list of ip hex addresses : mutually exclusive with -l & -a"
	echo "$name# -h    : display this help and exit"
}

# Main:
cmdline="$0 $@"
name=`basename $0 .sh`

path=$0
path=${path%/*}
#source $path/rootFSCommon.sh

rfsFolder=
mapsFile=
mltLog=
mafsLog=
ipAddress=
saMode=
ipfld=
while [ "$1" != "" ]; do
	case $1 in
		-r | --root )   shift
				rfsFolder=$1
				;;
		-maps )    	shift
				mapsFile=$1
				;;
		-mlt| --mltlog) shift
				mltLog=$1
				saMode="n"
				;;
		-mafs| --mafslog) shift
				mafsLog=$1
				saMode="n"
				;;
		-a )		shift
				ipAddress=$1
				[ -s "$ipAddress" ] && saMode="n" || saMode="y"
				;;
		-d )		shift
				ipfld=$1
				saMode="n"
				;;
		-h | --help )   usage
				exit
				;;
		* )             echo "$name# ERROR : unknown parameter in the command argument list!"
				usage
				exit 1
    esac
    shift
done

objdump=
platform=
if [ "$USE_SYSRES_PLATFORM" != "" ]; then
	platform=$(echo $USE_SYSRES_PLATFORM | tr '[:lower:]' '[:upper:]')
	case $platform in
		CANMORE  ) objdump=i686-cm-linux-objdump ;;
		BROADCOM ) objdump=mipsel-linux-objdump ;;
		       * ) 
			echo "$name# ERROR : unsupported $USE_SYSRES_PLATFORM platform"
			echo "$name# ERROR : USE_SYSRES_PLATFORM = {BROADCOM | CANMORE}"
			usage
			exit 1
	esac

	if [ "$(which $objdump)" == "" ]; then
		echo "$name# ERROR : Path to $objdump is not set!"
		usage
		exit
	fi
fi

if [ "$rfsFolder" == "" ] || [ ! -d "$rfsFolder" ]; then
	echo "$name# ERROR : rootFS folder $rfsFolder is not set!"
        usage
	exit
fi

if [ ! -e "$mapsFile" ]; then
	echo "$name# ERROR : $mapsFile file not found!"
        usage
	exit
fi

if [ "$saMode" == "" ]; then
	echo "$name# ERROR : a mandatory { -l | -a | -d } option is not set!"
        usage
	exit
fi

if [ "$ipfld" != "" ] && [ ! -e "$ipfld" ]; then
	echo "$name# ERROR : file descriptor is not set or empty!"
        usage
	exit
fi

if [ "$saMode" == "n" ]; then
	if [ "$mltLog" != "" ] && [ ! -e "$mltLog" ]; then
		echo "$name# ERROR : $mltLog file not found!"
		usage
		exit
	elif [ "$mafsLog" != "" ] && [ ! -e "$mafsLog" ]; then
		echo "$name# ERROR : $mafsLog file not found!"
		usage
		exit
	elif [ "$ipAddress" != "" ] && [ ! -e "$ipAddress" ]; then
		echo "$name# ERROR : $ipAddress file not found!"
		usage
		exit
	elif [ "$ipfld" != "" ]; then
		while read -r
		do
			if [ ! -s "$REPLY" ]; then
				echo "$name# ERROR : $ipfld file list descriptor's "$REPLY" file not found or empty!"
				exit 1
			fi
		done < "$ipfld"
		ipAddress=$ipfld.all
	fi
else
	ipAddress=${ipAddress#0x}
	if [[ $ipAddress = *[!0-9A-Fa-f]* ]]; then
		echo "$name# ERROR : instruction address $ipAddress is not a valid hex value!"
		usage
		exit
	fi
	ipAddress="0x$ipAddress"
fi

if [ ! -e $rfsFolder/version.txt ]; then
	rootFS=$(basename $rfsFolder)
	echo "$name# ERROR : $rfsFolder/version.txt file is not present. Using $rootFS folder basename!"
else
	rootFS=$(cat $rfsFolder/version.txt | grep -i imagename |  tr ': =' ':' | cut -d ':' -f2)
fi

procFile=$(head -n 1 $mapsFile | tr -s ' ' | cut -d ' ' -f6)
proc=$(basename "$procFile")

# Main:
echo "$cmdline" > $rootFS.$proc.log
if [ "$USE_SYSRES_PLATFORM" != "" ]; then
	echo "$name : platform  = $platform"  | tee -a $rootFS.$proc.log
	echo "$name : objdump   = $objdump"   | tee -a $rootFS.$proc.log
else
	echo "$name : WARNING   : USE_SYSRES_PLATFORM = {BROADCOM | CANMORE} is not set! Stripped ELF objects will not be resolved!"  | tee -a $rootFS.$proc.log
fi
echo "$name : rfsFolder = $rfsFolder" | tee -a $rootFS.$proc.log
echo "$name : rootFS    = $rootFS"    | tee -a $rootFS.$proc.log
echo "$name : process   = $proc"      | tee -a $rootFS.$proc.log
echo "$name : proc maps = $mapsFile"  | tee -a $rootFS.$proc.log
if [ "$saMode" == "n" ]; then
	if [ "$mltLog" != "" ]; then
		echo "$name : mlt log   = $mltLog" | tee -a $rootFS.$proc.log
		echo "$name : output    = $mltLog.resolved" | tee -a $rootFS.$proc.log
	elif [ "$mafsLog" != "" ]; then
		echo "$name : mafs log  = $mafsLog" | tee -a $rootFS.$proc.log
		echo "$name : output    = $mafsLog.resolved" | tee -a $rootFS.$proc.log
	elif [ "$ipfld" != "" ]; then
		echo "$name : ip descr  = $ipfld" | tee -a $rootFS.$proc.log
		echo "$name : output    = -.resolved / $ipAddress.elf.resolved" | tee -a $rootFS.$proc.log
	else
		echo "$name : addresses = $ipAddress" | tee -a $rootFS.$proc.log
		echo "$name : output    = $ipAddress.resolved / $ipAddress.elf.resolved" | tee -a $rootFS.$proc.log
	fi
else
	echo "$name : address   = $ipAddress" | tee -a $rootFS.$proc.log
fi
startTime=`cat /proc/uptime | cut -d ' ' -f1 | cut -d '.' -f1`
grep "r-xp" $mapsFile > $mapsFile.r-xp

if [ "$saMode" == "n" ]; then
	if [ "$mltLog" != "" ]; then
		# Allign caller address in the $mltLog
		cat /dev/null > $mltLog.aa
		while read sk1 sk2 sk3 sk4 address therest
		do
			[ -z "$sk1" ] || printf "%s %s %s %s 0x%08x %s\n" $sk1 $sk2 $sk3 $sk4 $((address)) "$therest" >> $mltLog.aa
		done < $mltLog

		# Build unsourced entries as ip-elf pair file from the MLT log
		cut -d ' ' -f5,19 $mltLog.aa > $mltLog.$proc.ip-elf
		ln -sf $mltLog.$proc.ip-elf ipAddr

		# Split the MLT log on sourced/unsourced entries
		awk -v noFileLineN="$NO_FILE_LINENUM_STR" '{ if ($19 == noFileLineN) { printf "%s\n", $0 > "mltLog.unsourced" } else { printf "%s\n", $0 > "mltLog.sourced" } }' $mltLog.aa
		[ -s mltLog.sourced ] && mv mltLog.sourced $mltLog.sourced
		[ -s mltLog.unsourced ] && mv mltLog.unsourced $mltLog.unsourced
		#cat $mltLog.unsourced | tee >(cut -d ' ' -f1-18 > $mltLog.unsourced.1) >(cut -d ' ' -f20- > $mltLog.unsourced.2) >/dev/null
		if [ -s $mltLog.unsourced ]; then
			cut -d ' ' -f-18 $mltLog.unsourced > $mltLog.unsourced.1
			cut -d ' ' -f20- $mltLog.unsourced > $mltLog.unsourced.2
		else
			# Clean up
			rm $mltLog.* ipAddr $mapsFile.r-xp

			# Finish up and exit.
			ln -sf $mltLog $mltLog.resolved

			printf "$name :           : Nothing to do. All entries resolved.\n" | tee -a $rootFS.$proc.log
			exit
		fi
	elif [ "$mafsLog" != "" ]; then
		# Allign caller address in the $mafsLog
		ipAddress=$mafsLog.$proc.ip
		cat /dev/null > $ipAddress
		grep -v "^____" $mafsLog | tr -s ' ' | cut -d ' ' -f2 | cut -b2- | cut -d ':' -f1 | while read address
		do
			[ -z "$address" ] || printf "0x%08x\n" $((address)) >> $ipAddress
		done
		sort -u $ipAddress -o $ipAddress

		cat /dev/null > $rootFS.$proc.ipAddr
		while read address
		do
			printf "0x%08x %s\n" $((address)) $NO_FILE_LINENUM_STR >> $rootFS.$proc.ipAddr
		done < "$ipAddress"
		ln -sf $rootFS.$proc.ipAddr ipAddr
		rm $ipAddress
	else 
		if [ "$ipfld" != "" ]; then
			cat /dev/null > $ipfld.all
			while read file
			do
				cat /dev/null > "$file.aa"
				while read address
				do
					[ -z "$address" ] || printf "0x%08x\n" $((address)) >> $file.aa
				done < "$file"
				cat $file.aa >> $ipfld.all
			done < "$ipfld"
			sort -u $ipfld.all -o $ipfld.all
		fi

		cat /dev/null > $rootFS.$proc.ipAddr
		while read address
		do
			[ -z "$address" ] || printf "0x%08x %s\n" $((address)) $NO_FILE_LINENUM_STR >> $rootFS.$proc.ipAddr
		done < "$ipAddress"
		ln -sf $rootFS.$proc.ipAddr ipAddr
	fi
else
	printf "0x%08x %s\n" $((ipAddress)) $NO_FILE_LINENUM_STR > $rootFS.$proc.ipAddr
	ln -sf $rootFS.$proc.ipAddr ipAddr
fi

# Build ip-elf pair file of the r-xp segment of all elf object of the process
cat /dev/null > $rootFS.$proc.ip-elf
cat $mapsFile.r-xp | tr -s ' ' | cut -d ' ' -f1,6 | while read range object
do
	start=0x$(echo $range | cut -d '-' -f1)
	end=0x$(echo $range | cut -d '-' -f2)
	printf "0x%08x %s%s\n0x%08x %s\n" $((start)) $object $ELF_START_STR $((end)) $ELF_END_STR >> $rootFS.$proc.ip-elf
done

# Build a map
cat $rootFS.$proc.ip-elf ipAddr | sort -sg -o $rootFS.$proc.ip-elf

n=1
entry=
start=
mkdir -p ip-elf
cat /dev/null > $rootFS.$proc.ip-elf.map
while read address object
do
	if [ "${object: -2}" == "$ELF_START_STR" ]; then
		entry=${object%$ELF_START_STR}
		start=$address
		cat /dev/null > ip-elf/$rootFS.$proc.ip-elf.$n
	elif [ "$object" == "$ELF_END_STR" ]; then
		if [ -s ip-elf/$rootFS.$proc.ip-elf.$n ]; then
			props=
			if [ -e "$rfsFolder$entry" ]; then
				if [ "$(readelf -S "$rfsFolder$entry" | grep "\.debug")" != "" ]; then
					props=$ELF_PROPS_DBG_SYM
				elif [ "$(file "$rfsFolder$entry" | grep "$ELF_PROPS_NOT_STR")" != "" ]; then
					props=$ELF_PROPS_NOT_STR
				else
					props=$ELF_PROPS_STRIPPED
				fi
			else
				echo "$name : WARNING   : ELF $entry object doesn't exist, ips will not be resolved!"  | tee -a $rootFS.$proc.log
				props=$ELF_PROPS_NOT_EXIST
			fi
			printf "%s%-3d\t%s-%s\t%s : %s\n" "ip-elf/$rootFS.$proc.ip-elf." $n "$start" "$address" "$entry" "$props" >> $rootFS.$proc.ip-elf.map
			n=$((n+1))
		fi
	else
		if [ "$object" == "$NO_FILE_LINENUM_STR" ]; then
			if [ "$entry" == "$procFile" ]; then
				echo $address >> ip-elf/$rootFS.$proc.ip-elf.$n
				[ ! -h ip-elf/$rootFS.$proc.ip-elf.$n.rt ] && ln -s $rootFS.$proc.ip-elf.$n ip-elf/$rootFS.$proc.ip-elf.$n.rt
			else
				echo $address >> ip-elf/$rootFS.$proc.ip-elf.$n.rt
				printf "0x%08x\n" $((address-start)) >> ip-elf/$rootFS.$proc.ip-elf.$n
			fi
		fi
	fi
done  < $rootFS.$proc.ip-elf

# Identify function / file name:line info of the unsourced entries based on a diff between ip addresses in the MLT log and a elf object start address
while read addrFile range object sep props
do
	if [ "$props" == "$ELF_PROPS_STRIPPED" ]; then
		if [ "$objdump" == "" ]; then
			awk '{printf "%s ??:?\n", $0}' $addrFile.rt > $addrFile.rt.resolved
		else
			$objdump -C -S "$rfsFolder$object" | grep "^[[:xdigit:]]\{8\}" | awk '{printf "0x%s\n", $0}' > $addrFile.func-map
			# create "start/end of executable section" entries and interlace them with the address(es)
			readelf -S "$rfsFolder$object" | grep " AX " | tr -s '[]' ' ' | tr -s ' ' | cut -d ' ' -f5,7 > $addrFile.exec-sec
			endst=0x$(tail -1 $addrFile.exec-sec | cut -d ' ' -f1)
			endsi=0x$(tail -1 $addrFile.exec-sec | cut -d ' ' -f2)
			start=0x$(head -1 $addrFile.exec-sec | cut -d ' ' -f1)
			end=$((endst + endsi - 1))
			printf "0x%08x %s\n" $((start)) "$ELF_PSEC_STARTOF_TEXT" | cat - $addrFile.func-map $addrFile > $addrFile.interlaced
			printf "0x%08x %s\n" $((end)) "$ELF_PSEC_ENDOF_TEXT" >> $addrFile.interlaced
			sort -sg $addrFile.interlaced -o $addrFile.interlaced
			rtload=$(grep "$addrFile" $rootFS.$proc.ip-elf.map | cut -f2 | cut -d '-' -f1)
			printf "0x%08x-0x%08x" $((start+rtload)) $((end+rtload)) > $addrFile.rt.range

			entry=
			cat /dev/null > $addrFile.resolved
			while read addrFunc funct
			do
				if [ "$funct" != "" ]; then
					entry=$funct
				elif [ "$entry" != "" ] && [ "$entry" != "$ELF_PSEC_ENDOF_TEXT" ]; then
					printf "%s %s\n" $addrFunc "$entry" >> $addrFile.resolved
				fi
			done  < $addrFile.interlaced
			[ -s $addrFile.resolved ] && cut -d ' ' -f2- $addrFile.resolved | paste -d ' ' $addrFile.rt - > $addrFile.rt.resolved
		fi
	elif [ "$props" == "$ELF_PROPS_NOT_EXIST" ]; then
		awk '{printf "%s ??:?\n", $0}' $addrFile.rt > $addrFile.rt.resolved
	else
		addr2line -Cpfa -e "$rfsFolder$object" @"$addrFile" | cut -d ' ' -f2- | paste -d ' ' $addrFile.rt - > $addrFile.rt.resolved
	fi
done < $rootFS.$proc.ip-elf.map

if [ -s $rootFS.$proc.ip-elf.map ]; then
	if [ "$saMode" == "n" ]; then
		if [ "$mltLog" != "" ]; then
			# Set sources of the unsourced entries in the MLT log with the identified function / file:line info
			#sort -k1 -g ip-elf/$rootFS.$proc.ip-elf.*.resolved -o $rootFS.$proc.ip-elf.resolved
			sort -k1 -g ip-elf/$rootFS.$proc.ip-elf.*.rt.resolved | cut -d ' ' -f2- > $rootFS.$proc.ip-elf.resolved
			[ -s $mltLog.sourced ] && sourced="$mltLog.sourced" || sourced=""
			if [ -s $mltLog.unsourced ]; then
				paste -d ' ' $mltLog.unsourced.1 $rootFS.$proc.ip-elf.resolved $mltLog.unsourced.2 > $mltLog.unsourced.resolved
				unsourced="$mltLog.unsourced.resolved"
			else
				unsourced=""
			fi
			cut -f2- $rootFS.$proc.ip-elf.map | awk '{printf "ELF  object #%03d   : ", NR; printf "%s\n", $0}' | cat - $sourced $unsourced | sort -k5 -g -o $mltLog.resolved
		elif [ "$ipfld" != "" ]; then
			cut -f2- $rootFS.$proc.ip-elf.map | awk '{printf "%s : ", $0; printf "ELF  object #%03d\n", NR}' | cat - ip-elf/$rootFS.$proc.ip-elf.*.rt.resolved | sort -g -o "$ipAddress".elf.resolved
			while read file
			do
				cat /dev/null > $file.resolved
				while read -r
				do
					grep "$REPLY" $ipAddress.elf.resolved | sort -k1 -u >> $file.resolved
				done < $file.aa
				[ "$(md5sum $file.aa | cut -d ' ' -f1)" != "$(cut -d ' ' -f1 $file.resolved | md5sum | cut -d ' ' -f1)" ] && printf "$name : ERROR     : File's $file.resolved backtrace is not in order!\n" | tee -a $rootFS.$proc.log || rm $file.aa
			done < "$ipfld"
		else
			cut -f2- $rootFS.$proc.ip-elf.map | awk '{printf "%s : ", $0; printf "ELF  object #%03d\n", NR}' | cat - ip-elf/$rootFS.$proc.ip-elf.*.rt.resolved | sort -g -o "$ipAddress".elf.resolved
			cat /dev/null > $ipAddress.resolved
			cut -d ' ' -f1 $rootFS.$proc.ipAddr | while read -r
			do
				grep "$REPLY" $ipAddress.elf.resolved | sort -k1 -u >> $ipAddress.resolved
			done

			if [ "$mafsLog" != "" ]; then
				cat /dev/null > $mafsLog.resolved
				while read anchor allocdescr at string therest
				do
					if [ -z "${anchor##[0-9]*:}" ]; then
						if [ "$string" == "$NO_FILE_LINENUM_STR" ]; then
							address=${allocdescr%%:*}
							printf "%s %s %s %s %s\n" $anchor $allocdescr $at "$(grep "${address:1}" $ipAddress.resolved | cut -d ' ' -f2-)" "$therest" >> $mafsLog.resolved
						else
							printf "%s %s %s %s %s\n" $anchor $allocdescr $at "$string" "$therest" >> $mafsLog.resolved
						fi
					elif [ "${anchor:0:3}" == "-0x" ]; then
						address=${anchor%%:*}
						printf "      %s @ %s\n" $anchor "$(grep "${address:1}" $ipAddress.resolved | cut -d ' ' -f2-)" >> $mafsLog.resolved
					elif [ "${anchor:0:5}" == "_____" ]; then
						printf "%s %s\n" $anchor $allocdescr >> $mafsLog.resolved
					fi
				done < "$mafsLog"
			fi
		fi
	else 
		if [ -s ip-elf/$rootFS.$proc.ip-elf.1.rt.resolved ]; then
			printf "$name : elfObject = %s\n" "$(cat $rootFS.$proc.ip-elf.map | cut -f2- | tr -s '\t' ' ')" | tee -a $rootFS.$proc.log
			printf "$name : source    = %s\n" "$(cat ip-elf/$rootFS.$proc.ip-elf.1.rt.resolved | cut -d ' ' -f2-)" | tee -a $rootFS.$proc.log
		else
			printf "$name : ERROR     : the address is outside of the exec section range %s of the \"%s\" ELF object\n" "$(cat ip-elf/$rootFS.$proc.ip-elf.1.rt.range)" "$(cut -f3 $rootFS.$proc.ip-elf.map | cut -d ' ' -f1)" | tee -a $rootFS.$proc.log
			printf "$name : source    = N/A\n" | tee -a $rootFS.$proc.log
		fi
	fi
else
	if [ "$saMode" == "y" ]; then
		printf "$name : ERROR     : the address is outside of the valid range of code segment addresses of all ELF objects!\n" | tee -a $rootFS.$proc.log
		printf "$name : source    = N/A\n" | tee -a $rootFS.$proc.log
	fi
fi

# Clean up
rm -rf ip-elf
rm $rootFS.$proc.ip-elf*
rm $mapsFile.r-xp
rm ipAddr
if [ "$saMode" == "n" ]; then
	if [ "$mltLog" != "" ]; then
		rm $mltLog.$proc.ip-elf $mltLog.aa
		[ -e $mltLog.sourced ] && rm $mltLog.sourced 
		[ -e $mltLog.unsourced ] && rm $mltLog.unsourced*
	else 
		[ "$ipfld" != "" ] && rm $ipfld.all
		rm $rootFS.$proc.ipAddr
	fi
else
	rm $rootFS.$proc.ipAddr
fi

endTime=`cat /proc/uptime | cut -d ' ' -f1 | cut -d '.' -f1`
execTime=`expr $endTime - $startTime`
printf "$name : Exec time : %02dh:%02dm:%02ds\n" $((execTime/3600)) $((execTime%3600/60)) $((execTime%60))

