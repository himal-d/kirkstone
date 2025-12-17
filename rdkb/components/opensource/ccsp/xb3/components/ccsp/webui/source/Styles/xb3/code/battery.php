<?php
/*
 * If not stated otherwise in this file or this component's Licenses.txt file the 
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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
*/
?>
<?php include('includes/header.php'); ?>

<!-- $Id: battery.php 3158 2010-01-08 23:32:05Z slemoine $ -->

<div id="sub-header">
	<?php include('includes/userbar.php'); ?>
</div><!-- end #sub-header -->

<?php include('includes/nav.php'); ?>

<script type="text/javascript">
$(document).ready(function() {
    comcast.page.init("Hardware > Battery", "nav-battery");

	if ("true" != "<?php echo getStr("Device.X_CISCO_COM_MTA.Battery.Installed"); ?>"){
		$(".div_battery [id^='bat_']").text("");
		$("#bat_power").text("AC");
		$("#bat_instal").text("No");
		return;
	}
	
	var percent	= $("#sta_batt").text().replace("Battery", "");
	var bat_remain	= "<?php echo getStr("Device.X_CISCO_COM_MTA.Battery.RemainingCharge"); ?>";
	$("#bat_remain").text(bat_remain + ' mAh ('+percent+')');
	
	var remain_time		= "<?php echo getStr("Device.X_CISCO_COM_MTA.Battery.RemainingTime"); ?>";
	var bat_hours	= Math.round(parseInt(remain_time)/6).toString();
	if (bat_hours.length <=1)
	{
		bat_hours = '0'+bat_hours;
	}

	$("#bat_hours").text(bat_hours.slice(0, -1) + "."+bat_hours.slice(-1) + ' hours');

});
</script>

<div id="content">
	<h1>Hardware > Battery</h1>
	<div id="educational-tip">
		<p class="tip">View information about the Gateway's battery status. </p>
		<p class="hidden">Battery power is for voice service only.</p>
	</div>

	<div class="module forms data div_battery">
		<table cellspacing="0" cellpadding="0" class="data" summary="This table shows battery status" >
		<tr>
			<th id="battery_metric">Battery Status</th>
			<th id="battery_status">&nbsp;</th>
		</tr>
		<tr class="odd">
			<td headers="battery_metric" class="row-label">Power status:</td>
			<td headers="battery_status" id="bat_power"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.PowerStatus"); ?></td>
		</tr>
		<tr>
			<td headers="battery_metric" class="row-label">Battery Installed:</td>
			<td headers="battery_status" id="bat_instal"><?php echo ("true"==getStr("Device.X_CISCO_COM_MTA.Battery.Installed") ? "Yes" : "No"); ?></td>
		</tr>
		<tr class="odd">
			<td headers="battery_metric" class="row-label">Battery Condition:</td>
			<td headers="battery_status" id="bat_condition"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.Condition"); ?></td>
		</tr>
		<tr>
			<td headers="battery_metric" class="row-label">Battery Status:</td>
			<td headers="battery_status" id="bat_status"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.Status"); ?></td>
		</tr>
		<tr class="odd">
			<td headers="battery_metric" class="row-label">Battery Life:</td>
			<td headers="battery_status" id="bat_life"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.Life"); ?></td>
		</tr>
		<tr>
			<td headers="battery_metric" class="row-label">Total Capacity:</td>
			<td headers="battery_status" id="bat_total"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.TotalCapacity"); ?> mAh</td>
		</tr>
		<tr class="odd">
			<td headers="battery_metric" class="row-label">Actual Capacity:</td>
			<td headers="battery_status" id="bat_actual"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.ActualCapacity"); ?> mAh</td>
		</tr>
		<tr>
			<td headers="battery_metric" class="row-label">Remaining Charge:</td>
			<td headers="battery_status" id="bat_remain">Loading...</td>
		</tr>
		<tr class="odd">
			<td headers="battery_metric" class="row-label">Remaining Time:</td>
			<td headers="battery_status" id="bat_hours" >Loading...</td>
		</tr>
		<tr>
			<td headers="battery_metric" class="row-label">Number of Cycles to date:</td>
			<td headers="battery_status" id="bat_cycles"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.NumberofCycles"); ?></td>
		</tr>
		<tr class="odd">
			<td headers="battery_metric" class="row-label">Battery Model Number:</td>
			<td headers="battery_status" id="bat_model"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.ModelNumber"); ?></td>
		</tr>
		<tr>
			<td headers="battery_metric" class="row-label">Battery Serial Number:</td>
			<td headers="battery_status" id="bat_serial"><?php echo getStr("Device.X_CISCO_COM_MTA.Battery.SerialNumber"); ?></td>
		</tr>
		</table>
	</div><!-- end .module -->
</div><!-- end #content -->

<?php include('includes/footer.php'); ?>
