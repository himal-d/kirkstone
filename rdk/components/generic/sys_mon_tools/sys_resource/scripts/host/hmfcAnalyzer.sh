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

# $0 : hmfcAnalyzer.sh is a Linux Host based script that identifies heap most frequent calls based on a single iteration MAFS log 

# Function: usage
function usage()
{
	echo "$name# Usage : `basename $0 .sh` [-mafs mafslog  [-s size]] | [-h]"
	echo "$name# MAFS single iteration log (heap) most frequent call analyzer"
	echo "$name# -mafs : a single iteration manadatory MAFS log file"
	echo "$name# -s    : an object size limit: all calls with object sizes of less than or equal to the size will be collected"
	echo "$name# -h    : display this help and exit"
}

# Main:
cmdline="$0 $@"
name=`basename $0 .sh`

mafsLog=
size=$((2**32))
while [ "$1" != "" ]; do
	case $1 in
		-mafs | --mafslog) shift
				mafsLog=$1
				;;
		-s )		shift
				size=$1
				;;
		-h | --help )   usage
				exit
				;;
		* )             echo "$name# ERROR   : unknown parameter in the command argument list!"
				usage
				exit 1
    esac
    shift
done

if [ ! -e "$mafsLog" ]; then
	echo "$name# ERROR   : $mafsLog file not found!"
        usage
	exit
fi

[ $size -eq $((2**32)) ] && ext="size-all" || ext="size-$size"

echo "$cmdline" > $mafsLog.log
echo "$name : mafsLog    = $mafsLog" | tee -a $mafsLog.log
echo "$name : size limit = $([ $size -eq $((2**32)) ] && echo "No" || echo "$size")"  | tee -a $mafsLog.log
echo "$name : output     = $mafsLog.$ext.hmfc" | tee -a $mafsLog.log

startTime=`cat /proc/uptime | cut -d ' ' -f1 | cut -d '.' -f1`

sentry=0
cat /dev/null > $mafsLog.ncr
cat /dev/null > $mafsLog.frq
while read anchor second at string content therest
do
	if [ -z "${anchor##[0-9]*:}" ] && [ ${content%(*} -le $size ]; then
		if [ -z "$therest" ]; then
			printf "%s %s %s %s %s\t" $anchor $second $at $string $content >> $mafsLog.ncr
		else
			printf "%s %s %s %s %s %s\t" $anchor $second $at $string $content "$therest" >> $mafsLog.ncr
		fi
		sentry=1
	elif [ "$sentry" == "1" ]; then
		if [ "${anchor:0:3}" == "-0x" ]; then
			printf "      %s\t" $anchor >> $mafsLog.ncr
		elif [ "${anchor:0:5}" == "_____" ]; then
			printf "%s %s\n" $anchor "$second" >> $mafsLog.ncr
			second=${second#*/*/}
			printf "%s\n" "${second%%/*}" >> $mafsLog.frq
			sentry=0
		fi
	else
		sentry=0
	fi
done < $mafsLog

paste -d ' ' $mafsLog.frq $mafsLog.ncr | sort -rns -k1 | cut -d ' ' -f2- | sed 's/\t/\n/g' > $mafsLog.$ext.hmfc

#Clean-up
rm $mafsLog.ncr $mafsLog.frq

endTime=`cat /proc/uptime | cut -d ' ' -f1 | cut -d '.' -f1`
execTime=`expr $endTime - $startTime`
printf "$name : Execution time: %02dh:%02dm:%02ds\n" $((execTime/3600)) $((execTime%3600/60)) $((execTime%60))

