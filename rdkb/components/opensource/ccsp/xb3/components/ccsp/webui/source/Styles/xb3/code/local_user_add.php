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

<!-- $Id: local_user_add.php 3116 2009-10-15 20:19:45Z cporto $ -->

<div id="sub-header">
	<?php include('includes/userbar.php'); ?>
</div><!-- end #sub-header -->

<?php include('includes/nav.php'); ?>

<script type="text/javascript">
$(document).ready(function() {
    comcast.page.init("Advanced > Local Users > Add User", "nav-local-user");

    $("input.reset").click(function() {
    	window.location = 'local_users.php';
    });
    
     $("#pageForm").validate({
        rules: {
            user_name: {
                required: true
            }
        }
    });

});
</script>

<div id="content">
	<h1>Advanced > Local Users > Add User</h1>

    <div id="educational-tip">
        <p class="tip"> This page needs some explanation text.</p>
    </div>
    
	<form id="pageForm" method="post" action="local_users.php">

	<div class="module forms">
		<h2>Add User</h2>
		<div class="form-row odd">
			<label for="user_name">Name:</label>
			<input type="text" id="user_name" name="user_name" class="text" value="Mom & Dad" />
		</div>

        <div class="form-row">
			<label for="password">Password:</label>
			<input type="password" id="password" name="password" class="text" />
		</div>
		
		
	</div> <!-- End Module -->
	<div class="form-btn">
		<input type="button" class="btn submit" value="Save"/>
		<input type="reset" class="btn alt reset" value="Cancel"/>
	</div>
</form>
</div><!-- end #content -->


<?php include('includes/footer.php'); ?>
