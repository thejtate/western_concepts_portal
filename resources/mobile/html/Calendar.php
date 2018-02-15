<?php $title = 'Calendar'; ?>
<?php include 'tpl/includes/head.inc'; ?>
<body class="page-calendar-mobile page">
<div class="outer-wrapper">
	<?php include 'tpl/layout/header.inc'; ?>
	<div class="inner-wrapper">
		<div class="content-wrapper">
			<div class="calendar-wrapper">
				<div class="calendar-header">
					<div class="date-nav">
						<div class="date-heading">
							<h3>September 2013</h3>
						</div>
						<ul class="pager">
							<li class="date-prev">
								<a href="#">Previous month</a>
							</li>
							<li class="date-next">
								<a href="#">Next month</a>
							</li>
						</ul>
					</div>
				</div>
				<div class="calendar-content">
          <ul>
            <li>
              <div class="wrapper-event">
                <div class="event-desc">
                  <div class="date">
                    <div class="date-hd">wed</div>
                    <div class="date-bd">2</div>
                  </div>
                  <div class="text-event">
                    <h5>Event Title</h5>
                    <div class="text">
                      <p>Musashi’s Japanese Steakhouse</p>
                    </div>
                  </div>
                  <div class="time-event"><span>5:00pm</span></div>
                </div>
              </div>
            </li>
            <li>
              <div class="wrapper-event wrapper-drop-down collapsed">
                <div class="btn-dd event-desc">
                  <div class="date">
                    <div class="date-hd">tue</div>
                    <div class="date-bd">8</div>
                  </div>
                  <div class="text-event">
                    <h5>Margarita Night</h5>
                    <div class="text">
                      <p>Musashi’s Japanese Steakhouse</p>
                    </div>
                  </div>
                  <div class="time-event"><span>5:00pm</span></div>
                </div>
                <div class="box-drop-down text">
                  <p>Join us for margaritas on Tuesday, Sept. 8th. $xx for margaritas before 7pm and $x after 9pm. Doors close at Xam.</p>
                </div>
              </div>
            </li>
            <li>
              <div class="wrapper-event">
                <div class="event-desc">
                  <div class="date">
                    <div class="date-hd">thur</div>
                    <div class="date-bd">10</div>
                  </div>
                  <div class="text-event">
                    <h5>Event Title</h5>
                    <div class="text">
                      <p>Musashi’s Japanese Steakhouse</p>
                    </div>
                  </div>
                  <div class="time-event"><span>5:00pm</span></div>
                </div>
              </div>
            </li>
          </ul>
				</div>
			</div>
		</div>
	</div>
  <div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>
</div>
</body>
</html>