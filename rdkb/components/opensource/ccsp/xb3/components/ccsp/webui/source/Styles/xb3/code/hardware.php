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

<!-- $Id: hardware.php 3158 2010-01-08 23:32:05Z slemoine $ -->

<div id="sub-header">
	<?php include('includes/userbar.php'); ?>
</div><!-- end #sub-header -->

<?php include('includes/nav.php'); ?>

<script type="text/javascript">
$(document).ready(function() {
    comcast.page.init("Gateway > Hardware > System Hardware", "nav-system-hardware");
});
</script>

<div id="content">
	<h1>Gateway > Hardware > System Hardware</h1>
	<div id="educational-tip">
		<p class="tip">View information about the Gateway's hardware.</p>
		<p class="hidden">You may need this information if you contact Comcast for troubleshooting assistance.</p>
	</div>
	<div class="module forms">
		<h2>System Hardware</h2>
		<div class="form-row odd">
			<span class="readonlyLabel">Model:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.ModelName"); ?></span>
		</div>
		<div class="form-row">
			<span class="readonlyLabel">Vendor:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.Manufacturer"); ?></span>
		</div>
		<div class="form-row odd">
			<span class="readonlyLabel">Hardware Revision:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.HardwareVersion"); ?></span>
		</div>
		<div class="form-row">
			<span class="readonlyLabel">Serial Number:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.SerialNumber"); ?></span>
		</div>
		<div class="form-row odd">
			<span class="readonlyLabel">Processor Speed:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.X_CISCO_COM_ProcessorSpeed"); ?> MHz</span>
		</div>
		<div class="form-row">
			<span class="readonlyLabel">DRAM Total Memory:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.MemoryStatus.Total"); ?> MB</span>
		</div>
		<div class="form-row odd">
			<span class="readonlyLabel">DRAM Used Memory:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.MemoryStatus.Used"); ?> MB</span>
		</div>
		<div class="form-row">
			<span class="readonlyLabel">DRAM Available Memory:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.MemoryStatus.Free"); ?> MB</span>
		</div>
		<div class="form-row odd">
			<span class="readonlyLabel">Flash Total Memory:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.Hardware"); ?> MB</span>
		</div>
		<div class="form-row">
			<span class="readonlyLabel">Flash Used Memory:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.Hardware_MemUsed"); ?> MB</span>
		</div>
		<div class="form-row odd">
			<span class="readonlyLabel">Flash Available Memory:</span> <span class="value">
			<?php echo getStr("Device.DeviceInfo.Hardware_MemFree"); ?> MB</span>
		</div>
	</div> <!-- end .module -->
</div><!-- end #content -->

<?php include('includes/footer.php'); ?>
