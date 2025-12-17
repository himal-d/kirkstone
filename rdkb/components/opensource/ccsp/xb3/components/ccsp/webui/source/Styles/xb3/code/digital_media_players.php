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

<div id="sub-header">
	<?php include('includes/userbar.php'); ?>
</div><!-- end #sub-header -->

<?php include('includes/nav.php'); ?>

<script type="text/javascript">
$(document).ready(function() {
    comcast.page.init("Advanced > Media Sharing > DLNA > Digital Media Players", "nav-dlna-media-players");
});
</script>

<div id="content">
	<h1>Advanced > Media Sharing > DLNA > Digital Media Players</h1>

	<div id="educational-tip">
		<p class="tip">Configure the DLNA Media Players.</p>
		<p class="hidden">Choose to allow or block the digital media players listed.</p>
	</div>

	<form  method="post" id="pageForm">
    <div class="module forms data">
		<h2>Digital Media Players(DLNA Compliant)</h2>
		<table class="data" cellpadding="0" cellspacing="0">
			<tbody>
				<tr>
					<td>Sony Play Station 3</td>
					<td>

						<ul class="radio-btns enable" id="devices-switch1">
							<li>
								<input  name="forwarding1" checked="checked" type="radio"  value="Enabled"/>
								<label for="forwarding_enabled">Allowed</label>
							</li>
							<li id="off">
								<input  name="forwarding1" type="radio"  value="Disabled"/>
								<label for="forwarding_disabled">Blocked</label>
							</li>
						</ul>
					</td>
				</tr>
				<tr class="odd">
					<td>wdtv</td>
					<td>

						<ul class="radio-btns enable" id="devices-switch2">
							<li>
								<input  name="forwarding2" checked="checked" type="radio"  value="Enabled"/>
								<label for="forwarding_enabled">Allowed</label>
							</li>
							<li id="off">
								<input  name="forwarding2" type="radio"  value="Disabled"/>
								<label for="forwarding_disabled">Blocked</label>
							</li>
						</ul>
					</td>
				</tr>
				<tr>
					<td>Sony Play Station 3</td>
					<td>

						<ul class="radio-btns enable" id="devices-switch3">
							<li>
								<input  name="forwarding3" checked="checked" type="radio"  value="Enabled"/>
								<label for="forwarding_enabled">Allowed</label>
							</li>
							<li id="off">
								<input  name="forwarding3" type="radio"  value="Disabled"/>
								<label for="forwarding_disabled">Blocked</label>
							</li>
						</ul>
					</td>
				</tr>
			</tbody>
		</table>

		</form>
		<div class="btn-group">
				<input type="button" value="Save Settings" class="btn" />
				</div>
</div><!-- end #content -->


<?php include('includes/footer.php'); ?>
