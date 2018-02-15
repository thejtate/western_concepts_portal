<!doctype html>
<html lang="en-US">
<head>
  <?php include 'src/com/meta.inc'; ?>
  <?php include 'src/com/styles.inc'; ?>
  <?php include 'src/com/scripts.inc'; ?>
</head>
<body class="page page-careers">
<div class="outer-wrapper">
  <?php include 'src/com/structs/header/header.inc'; ?>
  <div class="inner-wrapper">
    <div class="content-wrapper">
      <div class="content-item form-careers">
        <div class="title-form">
          <h1>Employment Application</h1>
        </div>
        <div class="form-site-custom">
          <form action="#">
            <?php include 'src/com/blocks/forms/step-1.inc'; ?>
            <?php include 'src/com/blocks/forms/step-2.inc'; ?>
            <?php include 'src/com/blocks/forms/step-3.inc'; ?>
            <?php include 'src/com/blocks/forms/step-4.inc'; ?>
            <?php include 'src/com/blocks/forms/step-5.inc'; ?>
            <?php include 'src/com/blocks/forms/step-6.inc'; ?>
            <?php include 'src/com/blocks/forms/step-7.inc'; ?>
          </form>
        </div>
      </div>
    </div>
  </div>
</div>
<?php include 'src/com/structs/footer/footer.inc'; ?>
</body>
</html>