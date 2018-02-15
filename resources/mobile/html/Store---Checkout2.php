<?php $title = 'Store---Checkout2'; ?>
<?php include 'tpl/includes/head.inc'; ?>
<body class="page-store page">
<div class="outer-wrapper">
<?php include 'tpl/layout/header.inc'; ?>
<div class="inner-wrapper">
<div class="content-wrapper">
<div class="content-item">
<div class="content-title">
  <div class="btn-wrapp pull-right">
    <div class="btn-submit">
      <a href="#">BACK TO STORE</a>
    </div>
  </div>
  <h1>Check Out</h1>
</div>
<div class="table-product">
  <div class="table-title">
    <h4>Your Cart</h4>
  </div>
  <table class="table">
    <thead>
    <tr>
      <th>ITEM(s)</th>
      <th class="col-qty">QTY</th>
      <th>PRICE</th>
    </tr>
    </thead>
    <tfoot>
    <tr>
      <td colspan="2">SUB-TOTAL</td>
      <td><span>$44.95</span></td>
    </tr>
    <tr>
      <td colspan="2">SHIPPING</td>
      <td><span>$5.00</span></td>
    </tr>
    <tr>
      <td colspan="2"><strong>TOTAL</strong></td>
      <td><strong>$49.95</strong></td>
    </tr>
    </tfoot>
    <tbody>
    <tr>
      <td>
        <div class="product-wrapper">
          <div class="image">
            <img src="theme/images/tmp/tmp-p-4.jpg" alt="img">
          </div>
          <div class="text-product">
            Gift Card
          </div>
          <div class="btn-remove">
            <a class="remove" href="#">REMOVE</a>
          </div>
        </div>
      </td>
      <td class="col-qty">
        1
      </td>
      <td>
        $25
      </td>
    </tr>
    </tbody>
  </table>
</div>
<div class="form-checkout form">
  <form action="#">
    <fieldset class="form-wrapper">
      <legend><span class="fieldset-legend">Billing Information</span></legend>
      <div class="form-field-text form-field field-name">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="First Name">
        </div>
      </div>
      <div class="form-field-text form-field field-last-name">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="Last Name">
        </div>
      </div>
      <div class="form-field-text form-field">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="COMPANY">
        </div>
      </div>
      <div class="form-field-text form-field">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="ADDRESS">
        </div>
      </div>
      <div class="form-field-text form-field field-city">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="CITY">
        </div>
      </div>
      <div class="form-field-text form-field field-state">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="STATE">
        </div>
      </div>
      <div class="form-field-text form-field field-zip">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="ZIP">
        </div>
      </div>
      <div class="form-field-text form-field field-phone">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="HOME PHONE">
        </div>
      </div>
      <div class="form-field-text form-field field-email">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="email">
        </div>
      </div>
    </fieldset>
    <fieldset class="form-wrapper">
      <legend><span class="fieldset-legend">Shipping Information</span></legend>
      <div class="form-field-checkbox form-field field-billing-address">
        <div class="form-item form-type-checkbox">
          <label for="id_checkbox_1">SAME AS BILLING ADDRESS</label>
          <input class="form-radio" type="checkbox">
        </div>
      </div>
      <div class="form-field-text form-field field-name">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="First Name">
        </div>
      </div>
      <div class="form-field-text form-field field-last-name">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="Last Name">
        </div>
      </div>
      <div class="form-field-text form-field">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="COMPANY">
        </div>
      </div>
      <div class="form-field-text form-field">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="ADDRESS">
        </div>
      </div>
      <div class="form-field-text form-field field-city">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="CITY">
        </div>
      </div>
      <div class="form-field-text form-field field-state">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="STATE">
        </div>
      </div>
      <div class="form-field-text form-field field-zip">
        <div class="form-item">
          <input type="text" class="form-text" placeholder="ZIP">
        </div>
      </div>
    </fieldset>
    <fieldset class="form-wrapper">
      <legend><span class="fieldset-legend">Payment Information</span></legend>
      <div class="form-field-select form-field field-type">
        <div class="form-item">
          <label>SELECT CARD TYPE</label>
          <select class="form-select">
            <option value="1">MASTERCARD</option>
            <option value="2">MASTERCARD</option>
            <option value="3">MASTERCARD</option>
            <option value="4">MASTERCARD</option>
            <option value="5">MASTERCARD</option>
            <option value="6">MASTERCARD</option>
            <option value="7">MASTERCARD</option>
            <option value="8">MASTERCARD</option>
            <option value="9">MASTERCARD</option>
            <option value="10">MASTERCARD</option>
          </select>
        </div>
      </div>
      <div class="form-field-text form-field field-expiration-date">
        <div class="form-item">
          <label>EXPIRATION DATE</label>
          <input type="text" class="form-text" />
        </div>
      </div>
      <div class="form-field-text form-field field-card">
        <div class="form-item">
          <input class="form-text" type="text" placeholder="CARD NUMBER" />
        </div>
      </div>
      <div class="form-field-text form-field field-code">
        <div class="form-item">
          <input class="form-text" type="text" placeholder="SECURITY CODE" />
        </div>
      </div>
      <div class="form-field-text form-field field-name-card">
        <div class="form-item">
          <input class="form-text" type="text" placeholder="NAME AS IT APPEARS ON CARD" />
        </div>
      </div>
    </fieldset>
    <div class="btn-wrapp">
      <div class="btn-submit pull-right">
        <input type="submit" value="submit">
      </div>
    </div>
    <div class="btn-gift">
      <span class="btn-title">HAVE A GIFT CARD?</span>
      <a href="#">Check Your Balance</a>
    </div>
  </form>
</div>
</div>
</div>
</div>
</div>
</body>
</html>