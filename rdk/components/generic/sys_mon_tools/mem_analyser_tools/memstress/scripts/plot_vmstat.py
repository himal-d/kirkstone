#! /usr/bin/env python
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2018 RDK Management
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

# Rough and dirty script for plotting vstat data collected through vmstat -n 1 output

import sys
import numpy as np
import matplotlib.pyplot as plt
import re


#column mappings
columns =    [2,        3,      4,     5,        6,                7,                  8,               9,                12,          13,        14,       15      ]
chartNames = ['swapd', 'free', 'buf', 'cache', 'swapped in (si)', 'swapped out (so)', 'blocks in (bi)', 'blocks out (bo)', 'cpu user', 'cpu sys', 'cpu id', 'cpu wa']
chartColor = ['r-', 'b-', 'g-', 'r--', 'b--', 'g--']


# parse arguments and collect files to plot
arguments = sys.argv

# collect all the files to be mapped
if len(arguments) < 2 : 
    print "need a minimum one name=value pair for parsing and drawing"

files={}
for pair in arguments[1:]:
    splitPair = pair.split("=")
    files[splitPair[0]] = splitPair[1]


print files 


# draw plot
for col in columns:
    maxlist = list()
    dataList = list()
    
    # collect data from supplied files
    for key in files.keys():
        data = []
        for line in open(files.get(key),'r').readlines():
            line = line.strip()
            line = re.sub(' +', ' ', line)
            data.append(line)
        dataArray = np.loadtxt(data, delimiter=" ", usecols = col, skiprows=2)
        dataList.append(dataArray)
        maxlist.append(np.amax(dataArray))
    
    pltLocal = plt
    pltLocal.axis([0, dataList[0].size+1, 0, max(maxlist)+1])
    pltLocal.ylabel(chartNames[columns.index(col)])
    pltLocal.xlabel("time (secs)")
    pltLocal.title("line chart for %s" % chartNames[columns.index(col)])
    
    index = 0
    legendText = "";
    plotHandles = []
    for key in files.keys():
        handle = pltLocal.plot(dataList[index], chartColor[index])
        plotHandles.append(handle[0])
        index=index+1
    
    plt.subplots_adjust(left=0.1, right=0.8)
    pltLocal.figlegend(tuple(plotHandles), tuple(files.keys()), loc="upper right")
    fig = pltLocal.gcf()
    #if you want to see while it is being drawn, uncomment this line
    #pltLocal.show()
    pltLocal.close()
    fig.savefig("%s_vmstat.png" % chartNames[columns.index(col)])
    print dataList


