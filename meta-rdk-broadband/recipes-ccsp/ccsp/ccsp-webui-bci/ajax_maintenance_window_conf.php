<?php
/*
 * If not stated otherwise in this file or this component's Licenses.txt
 * file the following copyright and licenses apply:
 *
 * Copyright 2021 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ajax_maintenance_window_conf.php
 *
 * Action handler via AJAX to configure maintenance window
 *
 * Author:	Anoop Ravi
 * Date:	Feb 17, 2017
 */

$startHr = $_POST['start_hr'];
$startMin = $_POST['start_min'];
$startSec = $_POST['start_sec'];
$endHr = $_POST['end_hr'];
$endMin = $_POST['end_min'];
$endSec = $_POST['end_sec'];

if ( $startHr!="" && $startMin!="" && $startSec!="" && $endHr!="" && $endMin!="" && $endSec!="" )
{
    $startHrInSec = $startHr * 60 * 60;
    $startMinInSec = $startMin * 60;
    $startTime = $startHrInSec + $startMinInSec + $startSec;

    $endHrInSec = $endHr * 60 * 60;
    $endMinInSec = $endMin * 60;
    $endTime = $endHrInSec + $endMinInSec + $endSec;

    if ($startTime==$endTime)
    {
        $response = array('status'=>'Failure');
        $response = array('msg'=>'Start time can not be same as End time');
    }
    else if (((($endTime-$startTime)<900)&&(($endTime-$startTime)>0))||(($startTime-$endTime)>85500))
    {
        $response = array('status'=>'Failure');
        $response = array('msg'=>'Maintenance window should be atleast 15 minutes');
    }
    else
    {
        setStr("Device.DeviceInfo.X_RDKCENTRAL-COM_MaintenanceWindow.FirmwareUpgradeStartTime",$startTime,true);
        setStr("Device.DeviceInfo.X_RDKCENTRAL-COM_MaintenanceWindow.FirmwareUpgradeEndTime",$endTime,true);
        $response = array('status'=>'success');
    }
}
else
{
    $response = array('status'=>'Failure');
    $response = array('msg'=>'Invalid Time');
}

l_output:
header("Content-Type: application/json");
echo json_encode($response);

?>
