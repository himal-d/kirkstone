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
# $0 : edfAnalyzer.sh is a Linux Host based script to analyze unreferenced 
#      code and data in object files and libraries for a given executable.

# Output:

# Variables:
ODDSFILTER="F \.text\|O .text\|O \.bss\|O \.data\|O \.rodata"
ODUSFILTER="\*UND\*"

# Function: usage
function usage()
{
	echo "$name# Usage : `basename $0 .sh` [-e exe [-f file list | -d folder ] [-l file list]] | [-h]"
	echo "$name# Unreferenced code and data analyzer"
	echo "$name# -e    : an elf executable"
	echo "$name# -f    : a file list of object files to analyze - mutually exclusive with -d"
	echo "$name# -l    : an optional file list of libraries to analyze"
	echo "$name# -d    : a folder with object files to analyze - mutually exclusive with -f"
	echo "$name# -V    : validation of used/unused symbol files"
	echo "$name# -s    : unused symbol file numericaly sorted in descending order"
	echo "$name# -r1/r2: rdf mode reduction: r1 - binary; r2 - binary and source"
	echo "$name# -h    : display this help and exit"
}

# Function: oddsBuilder - objdump defined symbol file builder
# $1: input file - compiled elf object file
# $2: output file - objdump defined symbol file (attribute, symbol)
# $3: output file - objdump defined symbol file (symbol, attribute)
function oddsBuilder()
{
	[ ! -e "$1".od ] && $objdump -tC "$1" > "$1".od
	grep "$ODDSFILTER" "$1".od | tr -s ' ' | cut -d ' ' -f1,3- | sed 's/ .text.*\t/.text__\t/;s/ .data.rel.ro.*\t/.data.rel.ro\t/;s/ .data.*\t/.data__\t/;s/ .bss.*\t/.bss___\t/;s/ .rodata.*\t/.rodata___\t/;s/.hidden //;s/[[:xdigit:]]\{8\}/&\t/;s/ //;s/ /\t/'  | awk -F'\t' '{printf "%s\t%s\t%s\t%s\n", $2, $1, $3, $4}' | sort -k2 -u | sort -k4 -o $2
	awk -F'\t' '{printf "%s\t%s\t%s\n", $4, $1, $3}' $2 | sort -k1 -o $3
}

# Function: odusBuilder - objdump undefined symbol file builder
# $1: input file - compiled elf object file
# $2: output file - objdump undefined symbol file
function odusBuilder()
{
	[ ! -e "$1".od ] && $objdump -tC "$1" > "$1".od
	grep "$ODUSFILTER" "$1".od | cut -f2- | tr -s ' ' | cut -d ' ' -f2- | sed 's/.hidden //' | sort -u -o $2
}

# Function: odsa2ods - odsa to ods file format conversion
function odsa2ods()
{
	awk -F'\t' '{printf "%s\t%s\t%s\n", $2, $3, $1}'
}

# Function: flcomplval - file list complement validation
# $1: input file: complete file list
# $2: input file: complement file list #1
# $3: input file: complement file list #2
# $4: input parameter: sort column
function flcomplval()
{
	[ "$4" == "" ] && col=1 || col=$4
	[ "$(sort -k$col "$1" | md5sum | cut -d ' ' -f1)" == "$(cat "$2" "$3" | sort -k$col | md5sum | cut -d ' ' -f1)" ] && echo "true" || echo "false"
}

# Function: odstotal - ods file metrics calculation
# $1: input file: ods file
# $2: output : ods calculated metrics
function odstotal()
{
#	awk -F'\t' '{        if ($1 == "F.text__") { ftext=strtonum("0x"$2); if (ftext) { Ftext+=ftext; FtextN++; } } \
	awk -F'\t' '{        if ($1 == "F.text__") { Ftext+=strtonum("0x"$2); FtextN++; } \
			else if ($1 == "O.text__") { Otext+=strtonum("0x"$2); OtextN++; } \
			else if ($1 == "O.data__") { Odata+=strtonum("0x"$2); OdataN++; } \
			else if ($1 == "O.rodata___") { Orodata+=strtonum("0x"$2); OrodataN++; } \
			else if ($1 == "O.data.rel.ro") { Odatarelro+=strtonum("0x"$2); OdatarelroN++; } \
			else if ($1 == "O.bss___") { Obss+=strtonum("0x"$2); ObssN++; } \
		    } \
		END { \
			if (Ftext) printf "\tF.text\t\t0x%08x / %8d\t%8d\n", Ftext, Ftext, FtextN; \
			if (Otext) printf "\tO.text\t\t0x%08x / %8d\t%8d\n", Otext, Otext, OtextN; \
			if (Odata) printf "\tO.data\t\t0x%08x / %8d\t%8d\n", Odata, Odata, OdataN; \
			if (Orodata) printf "\tO.rodata\t0x%08x / %8d\t%8d\n", Orodata, Orodata, OrodataN; \
			if (Odatarelro) printf "\tO.data.rel.ro\t0x%08x / %8d\t%8d\n", Odatarelro, Odatarelro, OdatarelroN; \
			if (Obss) printf "\tO.bss\t\t0x%08x / %8d\t%8d\n", Obss, Obss, ObssN; \
		    }' $1
}

# Function: odstotal - old ods file total metrics calculation
# $1: input file: ods file
# $2: output file: ods file with calculated total metrics
#function odstotalold()
#{
#	grep $'^\t' $1 | tr -s '\t' | \
#	awk -F'\t' '{ if ($2 == "F.text") { Ftext+=strtonum(substr($3,1,10)); FtextN+=strtonum(substr($4,1)); } \
#			else if ($2 == "O.text") { Otext+=strtonum(substr($3,1,10)); OtextN+=strtonum(substr($4,1)); } \
#			else if ($2 == "O.data") { Odata+=strtonum(substr($3,1,10)); OdataN+=strtonum(substr($4,1)); } \
#			else if ($2 == "O.rodata") { Orodata+=strtonum(substr($3,1,10)); OrodataN+=strtonum(substr($4,1)); } \
#			else if ($2 == "O.data.rel.ro") { Odatarelro+=strtonum(substr($3,1,10)); OdatarelroN+=strtonum(substr($4,1)); } \
#			else if ($2 == "O.bss") { Obss+=strtonum(substr($3,1,10)); ObssN+=strtonum(substr($4,1)); } \
#		    } \
#		END { \
#			if (Ftext) printf "\tF.text\t\t0x%08x / %8d\t%8d\n", Ftext, Ftext, FtextN; \
#			if (Otext) printf "\tO.text\t\t0x%08x / %8d\t%8d\n", Otext, Otext, OtextN; \
#			if (Odata) printf "\tO.data\t\t0x%08x / %8d\t%8d\n", Odata, Odata, OdataN; \
#			if (Orodata) printf "\tO.rodata\t0x%08x / %8d\t%8d\n", Orodata, Orodata, OrodataN; \
#			if (Odatarelro) printf "\tO.data.rel.ro\t0x%08x / %8d\t%8d\n", Odatarelro, Odatarelro, OdatarelroN; \
#			if (Obss) printf "\tO.bss\t\t0x%08x / %8d\t%8d\n", Obss, Obss, ObssN; \
#		    }' >> $2
#}

# Function: odstotalRead - ods file total metrics read back
# $1: input file: ods file
#    output     : ods file total metrics read back values
function odstotalRead()
{
	sed 's/^\t//;s/\t\t/\t/1' $1 | \
	awk -F'\t' '{ if ($1 == "F.text") { Ftext=strtonum(substr($2,1,10)); FtextN=strtonum(substr($3,1)); } \
		else if ($1 == "O.text") { Otext=strtonum(substr($2,1,10)); OtextN=strtonum(substr($3,1)); } \
		else if ($1 == "O.data") { Odata=strtonum(substr($2,1,10)); OdataN=strtonum(substr($3,1)); } \
		else if ($1 == "O.rodata") { Orodata=strtonum(substr($2,1,10)); OrodataN=strtonum(substr($3,1)); } \
		else if ($1 == "O.data.rel.ro") { Odatarelro=strtonum(substr($2,1,10)); OdatarelroN=strtonum(substr($3,1)); } \
		else if ($1 == "O.bss") { Obss=strtonum(substr($2,1,10)); ObssN=strtonum(substr($3,1)); } \
		} END { printf "%d %d %d %d %d %d %d %d %d %d %d %d\n", Ftext, Otext, Odata, Orodata, Odatarelro, Obss, FtextN, OtextN, OdataN, OrodataN, OdatarelroN, ObssN; }'
}

function odsRead()
{
	echo "$1" | awk '{ if ($1 == "F.text") { Ftext=strtonum(substr($2,1,10)); FtextN=strtonum(substr($3,1)); } \
		else if ($1 == "O.text") { Otext=strtonum(substr($2,1,10)); OtextN=strtonum(substr($3,1)); } \
		else if ($1 == "O.data") { Odata=strtonum(substr($2,1,10)); OdataN=strtonum(substr($3,1)); } \
		else if ($1 == "O.rodata") { Orodata=strtonum(substr($2,1,10)); OrodataN=strtonum(substr($3,1)); } \
		else if ($1 == "O.data.rel.ro") { Odatarelro=strtonum(substr($2,1,10)); OdatarelroN=strtonum(substr($3,1)); } \
		} END { printf "%d %d %d %d %d\n", Ftext, Otext, Odata, Orodata, Odatarelro; }'
}

# Function: odsrns - ods used/unused file format numeric sort in reverse order
# $1: input file: ods used/unused file
# $2: output file: ods used/unused file numerically sorted in reverse order
function odsrns()
{
	cat /dev/null > "$1".ncr
	cat /dev/null > "$1".size

	_entry_=0
	_entryTotal_=0
	while read
	do
		if [ "${REPLY:0:1}" == $'\t' ] || [ "$_entry_" == "0" ]; then
			read _Ftext_ _Otext_ _OData_ _Orodata_ _Odatarelro_ <<< $(echo $(odsRead "${REPLY}"))
			_entryTotal_=$((_entryTotal_+_Ftext_+ _Otext_+_OData_+_Orodata_+_Odatarelro_))
			printf "%s;" "${REPLY}" >> "$1".ncr
			_entry_=1
		else
			printf "%d\n" $_entryTotal_ >> "$1".size
			_entryTotal_=0
			printf "\n%s;" "${REPLY}" >> "$1".ncr
			_entry_=0
		fi
	done < "$1"
	printf "%d\n" $_entryTotal_ >> "$1".size
	printf "\n" >> "$1".ncr

	paste -d $' ' "$1".size "$1".ncr | sort -rns -k1 | cut -d ' ' -f2- | sed 's/;$//;s/;/\n/g' > "$2"
	#Cleanup
	#rm "$1".size "$1".ncr
}

# Function: odsvalidate - ods used/unused format file validation
# $1: input file: ods used/unused format total file
# $2: input file: ods used/unused format file - complement 1
# $3: input file: ods used/unused format file - complement 2
# $4: input file: validation type
# $5: output file: validation output
# Ftext, Otext, Odata, Orodata, Odatarelro, Obss, FtextN, OtextN, OdataN, OrodataN, OdatarelroN, ObssN
function odsvalidate()
{
	read _FtextTo_ _OtextTo_ _ODataTo_ _OrodataTo_ _OdatarelroTo_ _ObssTo_ _FtextToN_ _OtextToN_ _ODataToN_ _OrodataToN_ _OdatarelroToN_ _ObssToN_ <<< $(echo "$(odstotalRead $1)")
	read _FtextC1_ _OtextC1_ _ODataC1_ _OrodataC1_ _OdatarelroC1_ _ObssC1_ _FtextC1N_ _OtextC1N_ _ODataC1N_ _OrodataC1N_ _OdatarelroC1N_ _ObssC1N_ <<< $(echo "$(odstotalRead $2)")
	read _FtextC2_ _OtextC2_ _ODataC2_ _OrodataC2_ _OdatarelroC2_ _ObssC2_ _FtextC2N_ _OtextC2N_ _ODataC2N_ _OrodataC2N_ _OdatarelroC2N_ _ObssC2N_ <<< $(echo "$(odstotalRead $3)")

#	echo "$1: FtextTo=$_FtextTo_ OtextTo=$_OtextTo_ ODataTo=$_ODataTo_ OrodataTo=$_OrodataTo_ OdatarelroTo=$_OdatarelroTo_ ObssTo=$_ObssTo_ FtextToN=$_FtextToN_ OtextToN=$_OtextToN_ ODataToN=$_ODataToN_ OrodataToN=$_OrodataToN_ OdatarelroToN=$_OdatarelroToN_ ObssToN=$_ObssToN_"
#	echo "$2: FtextTo=$_FtextC1_ OtextTo=$_OtextC1_ ODataTo=$_ODataC1_ OrodataTo=$_OrodataC1_ OdatarelroC1=$_OdatarelroC1_ ObssC1=$_ObssC1_ FtextC1N=$_FtextC1N_ OtextC1N=$_OtextC1N_ ODataToN=$_ODataC1N_ OrodataC1N=$_OrodataC1N_ OdatarelroC1N=$_OdatarelroC1N_ ObssC1N=$_ObssC1N_"
#	echo "$3: FtextTo=$_FtextC2_ OtextTo=$_OtextC2_ ODataTo=$_ODataC2_ OrodataTo=$_OrodataC2_ OdatarelroC2=$_OdatarelroC2_ ObssC2=$_ObssC2_ FtextC2N=$_FtextC2N_ OtextC2N=$_OtextC2N_ ODataToN=$_ODataC2N_ OrodataC2N=$_OrodataC2N_ OdatarelroC2N=$_OdatarelroC2N_ ObssC2N=$_ObssC2N_"

	_failure_=
	(( $_FtextTo_ != $_FtextC1_ + $_FtextC2_ )) && _failure_="F.text:"
	(( $_OtextTo_ != $_OtextC1_ + $_OtextC2_ )) && _failure_=$_failure_"O.text:"
	(( $_ODataTo_ != $_ODataC1_ + $_ODataC2_ )) && _failure_=$_failure_"O.data:"
	(( $_OrodataTo_ != $_OrodataC1_ + $_OrodataC2_ )) && _failure_=$_failure_"O.rodata:"
	(( $_OdatarelroTo_ != $_OdatarelroC1_ + $_OdatarelroC2_ )) && _failure_=$_failure_"O.datarelro:"
	(( $_ObssTo_ != $_ObssC1_ + $_ObssC2_ )) && _failure_=$_failure_"O.bss:"

	(( $_FtextToN_ != $_FtextC1N_ + $_FtextC2N_ )) && _failure_=$_failure_"F.text#:"
	(( $_OtextToN_ != $_OtextC1N_ + $_OtextC2N_ )) && _failure_=$_failure_"O.text#:"
	(( $_ODataToN_ != $_ODataC1N_ + $_ODataC2N_ )) && _failure_=$_failure_"O.data#:"
	(( $_OrodataToN_ != $_OrodataC1N_ + $_OrodataC2N_ )) && _failure_=$_failure_"O.rodata#:"
	(( $_OdatarelroToN_ != $_OdatarelroC1N_ + $_OdatarelroC2N_ )) && _failure_=$_failure_"O.datarelro#:"
	(( $_ObssToN_ != $_ObssC1N_ + $_ObssC2N_ )) && _failure_=$_failure_"O.bss#:"
	#_failure_=${_failure_%:}
	if [ "$_failure_" != "" ]; then
		#echo "$4: $_failure_" >> $5
		echo "$_failure_" >> $5
	fi
}

# Main:
cmdline="$0 $@"
name=`basename $0 .sh`

path=$0
path=${path%/*}

exeFile=
objFolder=
objFileList=
libFileList=
validate="n"
rns="n"
excsList=
rdfAnalysis="r1"
while [ "$1" != "" ]; do
	case $1 in
		-e )	shift
			exeFile=$1
			;;
		-f ) 	shift
			objFileList=$1
			;;
		-l ) 	shift
			libFileList=$1
			;;
		-d ) 	shift
			objFolder=$1
			;;
		-V )	validate="y"
			;;
		-s )	rns="y"
			;;
		-r1 )	rdfAnalysis="r1"
			;;
		-r2 )	rdfAnalysis="r2"
			;;
		-x )	shift
			excsList=$1
			;;
		-h| --help)
			usage
			exit
			;;
		* )	echo "$name# ERROR : unknown parameter in the command argument list!"
			usage
			exit 1
	esac
	shift
done

if [ "$objFolder" != "" ] && [ "$objFileList" != "" ]; then
	echo "$name# ERROR : only -f or -d option should be set!"
	usage
	exit
fi

if [ "$objFolder" == "" ] && [ "$objFileList" == "" ]; then
	echo "$name# ERROR : either -f or -d option should be set!"
	usage
	exit
fi

objdump=
platform=
if [ "$USE_SYSRES_PLATFORM" != "" ]; then
	platform=$(echo $USE_SYSRES_PLATFORM | tr '[:lower:]' '[:upper:]')
	case $platform in
		CANMORE  ) objdump=i686-cm-linux-objdump ;;
		BROADCOM ) objdump=mipsel-linux-objdump
			   ar=mipsel-linux-ar
			   readelf=mipsel-linux-readelf ;;
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

if [ ! -e "$exeFile" ]; then
	echo "$name# ERROR : $exeFile file not found!"
	usage
	exit
fi
exeFileBN=$(basename $exeFile .sh)

if [ "$objFileList" != "" ]; then
	if [ ! -e "$objFileList" ]; then
		echo "$name# ERROR : $objFileList file not found!"
		usage
		exit
	else
		sort -u $objFileList -o $objFileList
		while read -r
		do
			if [ ! -s "$REPLY" ]; then
				echo "$name# ERROR : "$REPLY" file  in the $objFileList not found or empty!"
				exit 1
			fi
		done < "$objFileList"
	fi
fi

if [ "$libFileList" != "" ]; then
	if [ ! -e "$libFileList" ]; then
		echo "$name# ERROR : $libFileList file not found!"
		usage
		exit
	else
		while read -r
		do
			if [ ! -s "$REPLY" ]; then
				echo "$name# ERROR : "$REPLY" file in the $libFileList not found or empty!"
				exit 1
			fi
			sections=$(readelf -S "$REPLY" | sed -n 's/.*.debug_.*/.dbg/p;s/.*.shstrtab.*//p;s/.*.symtab.*/.symtab/p;s/.*.strtab.*/.strtab/p' | sort | uniq | tr -d '\n' | sed '$a\')
			if [[ $rdfAnalysis == "r1" ]] && [[ $sections != *.strtab* ]] && [[ $sections != *.symtab* ]]; then
				echo "$name# ERROR : rdf r1 analysis require $REPLY library (available sections \"$sections\") built with symbolic info !"
				exit 1
			fi
			if [[ $rdfAnalysis == "r2" ]] && [[ $sections != *.dbg* ]]; then
				echo "$name# ERROR : rdf r2 analysis require $REPLY library (available sections \"$sections\") built with -g option !"
				exit 1
			fi
		done < "$libFileList"
	fi
fi

if [ "$objFolder" != "" ]; then 
	if [ ! -d "$objFolder" ]; then
		echo "$name# ERROR : oject file folder $objFolder is not set!"
		usage
		exit
	else
		objFileList=$exeFileBN.edfa.o-files
		find $objFolder -maxdepth 1 -type f | grep "\.o\$" | sort -o $objFileList
	fi
fi

if [ "$excsList" != "" ] && [ ! -e "$excsList" ]; then
	echo "$name# ERROR : $excsList file not found!"
	usage
	exit
fi

# Only one library is supporetd for the moment.
LibFile=$(cat $libFileList)
LibFileA=${LibFile%.*}.a
$ar rcs $LibFileA $(cat $objFileList | tr '\n' ' ')

echo "$cmdline" > $exeFileBN.edfa.log
if [ "$USE_SYSRES_PLATFORM" != "" ]; then
	echo "$name : platform             = $platform"  | tee -a $exeFileBN.edfa.log
	echo "$name : objdump              = $objdump"   | tee -a $exeFileBN.edfa.log
else
	echo "$name# ERROR : USE_SYSRES_PLATFORM = {BROADCOM | CANMORE} is not set!"  | tee -a $rootFS.$proc.log
	exit
fi
echo "$name : Exe File             = $exeFile"     | tee -a $exeFileBN.edfa.log
echo "$name : Lib File             = $LibFile : sections=$sections"     | tee -a $exeFileBN.edfa.log
echo "$name : log File             = $exeFileBN.edfa.log" | tee -a $exeFileBN.edfa.log
echo "$name : rdfAnalysis type     = $rdfAnalysis" | tee -a $exeFileBN.edfa.log
objFileListSize=$(wc -l $objFileList | cut -d ' ' -f1)
[ "$objFolder" != "" ] && echo "$name : Lib object folder    = $objFolder (size = $objFileListSize)" | tee -a $exeFileBN.edfa.log || echo "$name : Lib object files     = $objFileList (size = $objFileListSize)" | tee -a $exeFileBN.edfa.log

# Main:
startTime=`cat /proc/uptime | cut -d ' ' -f1 | cut -d '.' -f1`

#Build objdump symbol file from an executable
oddsBuilder "$exeFile" "$exeFile".exe.ods "$exeFile".exe.odsa

#Build objdump symbol file from a static lib
oddsBuilder "$LibFileA" "$LibFileA".ods "$LibFileA".odsa

#Build objdump undefined symbol file from a list of libraries
if [ "$libFileList" != "" ]; then
	while read libfile
	do
		oddsBuilder "$libfile" "$libfile".ods "$libfile".odsa
		odusBuilder "$LibFileA" "$libfile".odu
		cat /dev/null > "$libfile".edfa.used
		cat /dev/null > "$libfile".ods.aused.short
		cat /dev/null > "$libfile".ods.tspfd.uu
		cat /dev/null > "$libfile".ods.tspfd.used
		cat /dev/null > "$libfile".ods.tspfd.unused
		cat /dev/null > "$libfile".ods.used
		cat /dev/null > "$libfile".ods.unused
		cat /dev/null > "$libfile".odsa.all-objfiles
		cat /dev/null > "$libfile".ods.total
		cat /dev/null > "$libfile".ods.used.total 
		cat /dev/null > "$libfile".ods.unused.total
		cat /dev/null > "$libfile".ods.used.rns.total
		cat /dev/null > "$libfile".ods.unused.rns.total
		cat /dev/null > "$libfile".ods.uu.rns.total
	done < "$libFileList"
fi

#Build objdump symbol files and compare them to the executable
cat /dev/null > $LibFile.edfa.unused
cat /dev/null > $LibFile.edfa.invalid.uusplit
while read objFile
do
	oddsBuilder "$objFile" "$objFile".ods "$objFile".odsa
	odusBuilder "$objFile" "$objFile".odu

	comm -1 "$exeFile".exe.odsa "$objFile".odsa | awk -F'\t' -v fn="$objFile" '{ if (match($0, "^\t")) { printf "%s\t%s\t%s\n", $3, $4, $2 > fn".ods.exe-used" } else { printf "%s\t%s\t%s\n", $2, $3, $1 > fn".ods.exe-unused" } }'
	touch "$objFile".ods.exe-used "$objFile".ods.exe-unused
	sort -k3 "$objFile".ods.exe-used -o "$objFile".ods.exe-used
	sort -k3 "$objFile".ods.exe-unused -o "$objFile".ods.exe-unused
	if [ "$libFileList" != "" ]; then
		anyLibUsed=0
		while read libfile
		do
			libfileBN=$(basename $libfile .sh)
			cut -f1 "$objFile".odsa | sort | comm -12 - $libfile.odu > "$objFile".$libfileBN.lib-aused.short
			[ -s "$objFile".$libfileBN.lib-aused.short ] && anyLibUsed=1
			if [ -s "$objFile".ods.exe-used ] || [ -s "$objFile".$libfileBN.lib-aused.short ]; then
#				echo "$objFile used : $([ -s "$objFile".ods.exe-used ] && echo "exe used" || echo "exe not used") : $([ -s "$objFile".$libfileBN.lib-aused.short ] && echo "lib used" || echo "lib not used")"
				echo "$objFile" >> "$libfile".edfa.used
#			else
#				echo "$objFile not used"
			fi

			if [ -s "$objFile".$libfileBN.lib-aused.short ]; then 
				grep -v -F -f "$objFile".$libfileBN.lib-aused.short "$objFile".ods.exe-unused > "$objFile".ods.unused
				awk -F'\t' '{printf "%s\t%s\t%s\n", $3, $1, $2}' "$objFile".ods.unused | sort | comm -13 - "$objFile".odsa | odsa2ods > "$objFile".ods.used
				rm "$objFile".ods.exe-used "$objFile".ods.exe-unused
			else
				mv "$objFile".ods.exe-used "$objFile".ods.used
				mv "$objFile".ods.exe-unused "$objFile".ods.unused
			fi

			used=
			if [ -s "$objFile".ods.used ]; then
				used=$(odstotal "$objFile".ods.used)
				printf "%s\n%s\n" "$objFile:" "$used" >> "$libfile".ods.tspfd.used
			fi
			unused=
			if [ -s "$objFile".ods.unused ]; then
				unused=$(odstotal "$objFile".ods.unused)
				printf "%s\n%s\n" "$objFile:" "$unused" >> "$libfile".ods.tspfd.unused
			fi

			echo "$objFile:" >> "$libfile".ods.tspfd.uu
			[ -n "$used" ] && printf "used:\n%s\n" "$used" >> "$libfile".ods.tspfd.uu
			[ -n "$unused" ] && printf "unused:\n%s\n" "$unused" >> "$libfile".ods.tspfd.uu

			cat "$objFile".odsa >> "$libfile".odsa.all-objfiles
			cat "$objFile".ods.used >> "$libfile".ods.used
			cat "$objFile".ods.unused >> "$libfile".ods.unused

			[ -s "$objFile".$libfileBN.lib-aused.short ] && cat "$objFile".$libfileBN.lib-aused.short >> "$libfile".ods.aused.short

			# Cleanup
			rm "$objFile".$libfileBN.lib-aused.short

		done < "$libFileList"
		if [ ! -s "$objFile".ods.used ] && [ "$anyLibUsed" == "0" ]; then
			echo "$objFile" >> $LibFile.edfa.unused
		fi
	fi

	if [ "$validate" == "y" ]; then
		cut -f1,3- "$objFile".ods > "$objFile".ods.tmp
		md5value=$(flcomplval "$objFile".ods.tmp "$objFile".ods.used "$objFile".ods.unused 3)
		rm "$objFile".ods.tmp
		if [ "$md5value" == "true" ]; then
			rm "$objFile".odsa
		else
			echo "$objFile".ods >> $LibFile.edfa.invalid.uusplit
		fi
	else
		# Cleanup
		rm "$objFile".odsa
	fi
done < "$objFileList"

# Account for LibFile private symbols
comm -13 "$LibFileA".odsa "$LibFile".odsa | odsa2ods > "$LibFile".ods.private.symbols
if [ -s "$LibFile".ods.private.symbols ]; then
	odstotal "$LibFile".ods.private.symbols > "$LibFile".ods.private
	printf "%s\n" "$LibFile.ods.private.symbols:" >> "$LibFile".ods.tspfd.used
	cat "$LibFile".ods.private.symbols >> "$LibFile".ods.used
	cat "$LibFile".ods.private >> "$LibFile".ods.tspfd.used
	rm "$LibFile".ods.private
fi

sort -u "$LibFile".odsa.all-objfiles -o "$LibFile".odsa.all-objfiles
comm -13 "$LibFile".odsa "$LibFile".odsa.all-objfiles | odsa2ods > "$LibFile".ods.discrepancy

[ -s "$LibFile".ods.discrepancy ] && cut -f3 "$LibFile".ods.discrepancy >> "$LibFile".ods.aused.short

sort -k3 -u "$LibFile".ods.used -o "$LibFile".ods.used
sort -k3 -u "$LibFile".ods.unused -o "$LibFile".ods.unused
odstotal "$LibFile".ods.used > "$LibFile".ods.used.total
odstotal "$LibFile".ods.unused > "$LibFile".ods.unused.total

cut -f1,3- "$LibFile".ods > "$LibFile".ods.tmp
odstotal "$LibFile".ods.tmp > "$LibFile".ods.total
rm "$LibFile".ods.tmp

comm -13 "$exeFile".exe.odsa "$LibFile".odsa > "$LibFile".odsa.exe-unused
if [ "$rdfAnalysis" == "r1" ]; then
	sort -u "$LibFile".ods.aused.short -o "$LibFile".ods.aused.short
	grep -F -f "$LibFile".ods.aused.short  "$LibFile".odsa | sort -o "$LibFile".odsa.aused
	if [ $(wc -l $LibFile.ods.aused.short | cut -d ' ' -f1) > $(wc -l "$LibFile".odsa.aused | cut -d ' ' -f1) ]; then
		# workaround start
		cut -f1 "$LibFile".odsa.aused | sort -o "$LibFile".ods.aused.2.short
		comm -13 "$LibFile".ods.aused.short "$LibFile".ods.aused.2.short > "$LibFile".ods.aused.discr.short
		grep -v -F -f "$LibFile".ods.aused.discr.short "$LibFile".odsa.aused > "$LibFile".odsa.aused.tmp
		mv "$LibFile".odsa.aused.tmp "$LibFile".odsa.aused
		rm "$LibFile".ods.aused.2.short
		# workaround end
	fi
	comm -23 "$LibFile".odsa.exe-unused "$LibFile".odsa.aused > "$LibFile".odsa.unused
	cut -f1 "$LibFile".odsa.unused | grep -F -f - "$LibFile".ods  | sort -k2 -o "$LibFile".ods.lib-unused

	rm "$LibFile".odsa.aused  "$LibFile".odsa.unused
else
	cut -f1 "$LibFile".odsa.exe-unused | grep -F -f - "$LibFile".ods  | sort -k2 -o "$LibFile".ods.lib-unused
fi

sort -u "$LibFile".edfa.used -o "$LibFile".edfa.used
if [ "$rdfAnalysis" == "r2" ]; then
	# Account for excluded symbol list
	if [ -n "$excsList" ]; then
		mv "$LibFile".ods.lib-unused "$LibFile".ods.lib-unused.tmp
		grep -v -F -f $excsList "$LibFile".ods.lib-unused.tmp | sort -k2 -o "$LibFile".ods.lib-unused
		rm "$LibFile".ods.lib-unused.tmp
	fi

	grep "F.text__" "$LibFile".ods.lib-unused | cut -f2 | awk -F'\t' '{ printf "0x%08x\n", strtonum("0x"$1) }' > "$LibFile".ods.lib-unused.addr
	# no header, no unresolved file/lines
	addr2line -Cp -e $LibFile @"$LibFile".ods.lib-unused.addr | grep -v ":0$\|\.h:" > "$LibFile".ods.lib-unused.file-line
	#addr2line -Cpfa -e $LibFile @"$LibFile".ods.lib-unused.addr | grep -v ":0$\|\.h:" > "$LibFile".ods.lib-unused.file-line

	# Create an rdf source list file
	cut -d ':' -f1 "$LibFile".ods.lib-unused.file-line | sort -u -o "$LibFile".ods.lib-unused.src

	# Create a list of completely unused sources
	cat /dev/null > $LibFile.edfa.unused.src
	while read -r file; do
		src=$(grep "\*ABS\*" $file.od | cut -f2 | cut -d ' ' -f2 | grep -v "\.h$")
		[ "$src" != "" ] && echo "$src" >> $LibFile.edfa.unused.src
	done < $LibFile.edfa.unused
	sort -u $LibFile.edfa.unused.src -o $LibFile.edfa.unused.src

	# Remove completely unused sources
	grep -F -f $LibFile.edfa.unused.src "$LibFile".ods.lib-unused.src | sort -o "$LibFile".ods.lib-unused.src.unused
	comm -13 "$LibFile".ods.lib-unused.src.unused "$LibFile".ods.lib-unused.src > "$LibFile".ods.lib-unused.src.used

	#  Reset temporary rdf source descriptors
	cat /dev/null > "$LibFile".ods.lib-unused.src.missing
	while read -r file; do
		if [ -s "$file" ]; then
			cat /dev/null > "$file".fsl
			cat /dev/null > "$file".sed
		else
			echo "$file" >> "$LibFile".ods.lib-unused.src.missing
		fi
	done < "$LibFile".ods.lib-unused.src.used
	# Remove missing files from the scope if any
	sort -u "$LibFile".ods.lib-unused.src.missing -o "$LibFile".ods.lib-unused.src.missing
	if [ -s "$LibFile".ods.lib-unused.src.missing ]; then
		comm -23 "$LibFile".ods.lib-unused.src.used "$LibFile".ods.lib-unused.src.missing > "$LibFile".ods.lib-unused.src.used.tmp
		mv "$LibFile".ods.lib-unused.src.used.tmp "$LibFile".ods.lib-unused.src.used
	else
		rm "$LibFile".ods.lib-unused.src.missing
	fi

	# Create lib-unused function start line files
	while IFS=':' read -r file line; do
		printf "%d:{\n" $line >> "$file".fsl
	done < "$LibFile".ods.lib-unused.file-line

	# Create lib-unused function start line files
	while read -r file; do
		grep -n "[{}]" "$file"| sed 's/[[:blank:]]//g;s/\r//' > "$file".fdl
	done < "$LibFile".ods.lib-unused.src.used

	# Compare lib-unused function start lines with function descriptor lines and create lib-unused function source sed files
	while read -r file; do
#		echo "sed: $file"
		sort -t: -k1 -n -u "$file".fsl -o "$file".fsl
		cat "$file".fsl "$file".fdl | sort -t: -k1 -n | uniq -c | sed 's/^ *//' | awk -v fileName="$file".sed -F' |:' 'BEGIN {search=0; } \
			{ \
			if ($1 == 2) \
				{ search=1; bc=1; bsl=$2; } \
			else \
				{ bc+=gsub("[{]", "") - gsub("[}]", "") } \
			#printf "%s : 1= %s 2= %s 3= %s : bc = %d : { = %d : } = %d\n", $0, $1, $2, $3, bc, gsub("[{]", ""), gsub("[}]", ""); \
			if ( search == 1 && bc == 0) \
				{search=0; printf "%di\\#if 0 //rdf\n%da\\#endif //rdf\n", bsl-1, $2 >> fileName }\
			}'
	done < "$LibFile".ods.lib-unused.src.used

	# Create lists of modified rdf sources to be rebuilt and unmodified used sources whose binaries do not have to be rebuilt
	cat /dev/null > "$LibFile".edfa.used-unmodified		# unmodified used binaries that not needed to be rebuilt
	cat /dev/null > "$LibFile".edfa.used.rdfsrc		# modified used rdf sources to be rebuilt
	while read -r objFile; do
		src=$(grep "\*ABS\*" $objFile.od | cut -f2 | cut -d ' ' -f2)
		filename=${src%.*} 
		ext=${src##*.}
		if [ -s $src.sed ]; then
			sed -f $src.sed $src > $filename.rdf.$ext
			echo $filename.rdf.$ext >> "$LibFile".edfa.used.rdfsrc
#			echo "rdf: $filename.rdf.$ext"
#			echo "$objFile : $filename.rdf.$ext" >> "$LibFile".edfa.used.rdfsrc.2
		else
			echo "$objFile" >> "$LibFile".edfa.used-unmodified
		fi
	done < "$LibFile".edfa.used	# traverse only through used & partially used binaries
	sort -u "$LibFile".edfa.used-unmodified -o "$LibFile".edfa.used-unmodified
fi

# Numeric sort in descendig order of the used/unused/uu format files
if [ "$rns" == "y" ]; then
	odsrns "$LibFile".ods.tspfd.used "$LibFile".ods.tspfd.used.rns
	odsrns "$LibFile".ods.tspfd.unused "$LibFile".ods.tspfd.unused.rns

	if [ -s "$LibFile".ods.private.symbols ]; then
		sed 's/;/;used:;/;$ d' "$LibFile".ods.tspfd.used.ncr > "$LibFile".ods.tspfd.used.ncr.tmp
	else
		sed 's/;/;used:;/' "$LibFile".ods.tspfd.used.ncr > "$LibFile".ods.tspfd.used.ncr.tmp
	fi
	paste -d '!' "$LibFile".ods.tspfd.unused.ncr "$LibFile".ods.tspfd.unused.size | sort | sed 's/;/;unused:;/' > "$LibFile".ods.tspfd.unused.ncr.tmp
	join -a1 -a2 -t';' -j1 "$LibFile".ods.tspfd.unused.ncr.tmp "$LibFile".ods.tspfd.used.ncr.tmp > "$LibFile".ods.tspfd.uu.ncr.tmp
	cut "$LibFile".ods.tspfd.uu.ncr.tmp -d '!' -f2 | cut -d ';' -f1 > "$LibFile".ods.tspfd.uu.ncr.size
	paste -d ' ' "$LibFile".ods.tspfd.uu.ncr.size "$LibFile".ods.tspfd.uu.ncr.tmp | sort -rns -k1 | cut -d ' ' -f2- | sed 's/![0-9]\+;*//;s/;$//;s/;/\n/g' > "$LibFile".ods.tspfd.uu.rns

	rm "$LibFile".ods.tspfd.used.size "$LibFile".ods.tspfd.used.ncr
	rm "$LibFile".ods.tspfd.unused.size "$LibFile".ods.tspfd.unused.ncr
	rm "$LibFile".ods.tspfd.used.ncr.tmp "$LibFile".ods.tspfd.unused.ncr.tmp "$LibFile".ods.tspfd.uu.ncr.size "$LibFile".ods.tspfd.uu.ncr.tmp
fi

echo "$name : Lib used files       = $LibFile.edfa.used (size = $(wc -l $LibFile.edfa.used | cut -d ' ' -f1))" | tee -a $exeFileBN.edfa.log
echo "$name : Lib unused files     = $LibFile.edfa.unused (size = $(wc -l $LibFile.edfa.unused | cut -d ' ' -f1))" | tee -a $exeFileBN.edfa.log
echo "$name : Lib total            = "$LibFile".ods.total :" | tee -a $exeFileBN.edfa.log
cat "$LibFile".ods.total | tee -a $exeFileBN.edfa.log
echo "$name : Lib used total       = "$LibFile".ods.used.total :" | tee -a $exeFileBN.edfa.log
cat "$LibFile".ods.used.total | tee -a $exeFileBN.edfa.log
echo "$name : Lib unused total     = "$LibFile".ods.unused.total :" | tee -a $exeFileBN.edfa.log
cat "$LibFile".ods.unused.total | tee -a $exeFileBN.edfa.log
if [ -s "$LibFile".ods.discrepancy ]; then
	odstotal "$LibFile".ods.discrepancy > "$LibFile".ods.discrepancy.total
	echo "$name : LibFile  discrepancy = "$LibFile".ods.discrepancy :" | tee -a $exeFileBN.edfa.log
	cat "$LibFile".ods.discrepancy.total | tee -a $exeFileBN.edfa.log
	rm "$LibFile".ods.discrepancy.total
else
	rm "$LibFile".ods.discrepancy
fi

if [ "$validate" == "y" ]; then
	cat /dev/null > $LibFile.edfa.invalid.sections
	# "$LibFile".ods.total "$LibFile".ods.used.total "$LibFile".ods.unused.total validation
	odsvalidate "$LibFile".ods.total "$LibFile".ods.used.total "$LibFile".ods.unused.total "total" $LibFile.edfa.invalid.sections

#	if [ "$rns" == "y" ]; then
#		# "$LibFile".ods.total "$LibFile".ods.tspfd.used.rns "$LibFile".ods.tspfd.unused.rns validation
#		odstotalold "$LibFile".ods.tspfd.used.rns "$LibFile".ods.used.rns.total
#		odstotalold "$LibFile".ods.tspfd.unused.rns "$LibFile".ods.unused.rns.total
#		odsvalidate "$LibFile".ods.total "$LibFile".ods.used.rns.total "$LibFile".ods.unused.rns.total "rns  " $LibFile.edfa.invalid.sections
#
#		# "$LibFile".ods.total "$LibFile".ods.tspfd.uu.rns validation
#		odstotalold "$LibFile".ods.tspfd.uu.rns "$LibFile".ods.uu.rns.total
#		odsvalidate "$LibFile".ods.total "$LibFile".ods.uu.rns.total /dev/null "uurns" $LibFile.edfa.invalid.sections
#	fi

	if [ -s $LibFile.edfa.invalid.uusplit ]; then
		echo "$name : used/unused split    = failed for $(wc -l $LibFile.edfa.invalid.uusplit| cut -d ' ' -f1) files" | tee -a $exeFileBN.edfa.log
	else
		rm $LibFile.edfa.invalid.uusplit
		echo "$name : used/unused split    = succeded" | tee -a $exeFileBN.edfa.log
	fi
	if [ -s $LibFile.edfa.invalid.sections ]; then
		awk -F ':' -v sn="$name" '{ printf "%s : section validation   = failed for %d cases : %s\n", sn, NF-1, $0 }' "$LibFile".edfa.invalid.sections | tee -a $exeFileBN.edfa.log
	else
		rm $LibFile.edfa.invalid.sections
		echo "$name : section validation   = succeded" | tee -a $exeFileBN.edfa.log
	fi
else
	rm  $LibFile.edfa.invalid.uusplit
fi

echo "$name : Lib all symbols      = "$LibFile".ods" | tee -a $exeFileBN.edfa.log
echo "$name : Lib used symbols     = "$LibFile".ods.used" | tee -a $exeFileBN.edfa.log
echo "$name : Lib unused symbols   = "$LibFile".ods.unused" | tee -a $exeFileBN.edfa.log
echo "$name : Lib used/unused tspfd= "$LibFile".ods.tspfd.uu" | tee -a $exeFileBN.edfa.log
echo "$name : Lib used tspfd       = "$LibFile".ods.tspfd.used" | tee -a $exeFileBN.edfa.log
echo "$name : Lib unused tspfd     = "$LibFile".ods.tspfd.unused" | tee -a $exeFileBN.edfa.log
[ -s "$LibFile".edfa.invalid.uusplit ] && echo "$name : used/unused split    = "$LibFile".edfa.invalid.uusplit" | tee -a $exeFileBN.edfa.log
[ -s "$LibFile".edfa.invalid.sections ] && echo "$name : section validation   = "$LibFile".edfa.invalid.sections" | tee -a $exeFileBN.edfa.log
[ -s "$LibFile".ods.lib-unused.src.missing ] && echo "$name : Missing source files = "$LibFile".ods.lib-unused.src.missing" | tee -a $exeFileBN.edfa.log
echo "$name : tspfd                = \"total symbols per file\" distribution" | tee -a $exeFileBN.edfa.log

# Cleanup
rm "$exeFile".od "$exeFile".exe.odsa "$LibFile".odu "$LibFile".odsa "$LibFile".odsa.exe-unused
rm "$LibFileA".od "$LibFileA".ods "$LibFileA".odsa
rm "$LibFile".ods.lib-unused*
rm "$LibFile".od "$LibFile".odsa.all-objfiles "$LibFile".ods.aused.short
rm "$LibFile".ods.used.rns.total "$LibFile".ods.unused.rns.total "$LibFile".ods.uu.rns.total
while read -r objFile; do rm $objFile.od*; done < "$objFileList"
rm "$objFileList"

endTime=`cat /proc/uptime | cut -d ' ' -f1 | cut -d '.' -f1`
execTime=`expr $endTime - $startTime`
printf "$name : Exec time : %02dh:%02dm:%02ds\n" $((execTime/3600)) $((execTime%3600/60)) $((execTime%60))

