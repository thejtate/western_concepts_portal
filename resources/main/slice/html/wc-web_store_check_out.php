<!doctype html>
<html lang="en-US">
<head>
  <?php include 'src/com/meta.inc'; ?>
  <?php include 'src/com/styles.inc'; ?>
  <?php include 'src/com/scripts.inc'; ?>
</head>
<body class="page page-store">
<div class="outer-wrapper">
  <?php include 'src/com/structs/header/header.inc'; ?>
  <div class="inner-wrapper">
    <div class="content-wrapper ">
      <div class="content-item">
        <div class="title-content">
          <h3>Check out</h3>
          <div class="btn-wrapp pull-right">
            <div class="btn-submit">
              <a href="#">BACK TO STORE</a>
            </div>
          </div>
        </div>
        <div class="table-product">
          <div class="table-title">
            <h4>Your Cart</h4>
          </div>
          <table class="table">
            <thead>
            <tr>
              <th>ITEM</th>
              <th>QTY</th>
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
                <div class="image">
                  <img src="images/tmp/_tmp_sh_min_1.jpg" alt="img" />
                </div>
                <div class="text-product">
                  Gift Card
                  <div class="data-product">
                    <span>COLOR: GREEN</span>
                    <span>SIZE: LARGE</span>
                  </div>
                </div>

                <div class="btn-remove">
                  <a class="remove" href="#">REMOVE</a>
                </div>
              </td>
              <td>
                1
              </td>
              <td>
                $25
              </td>
            </tr>
            <tr>
              <td>
                <div class="image">
                  <img src="images/tmp/_tmp_sh_min_2.jpg" alt="img" />
                </div>
                <span class="text-product">
                  Gift Card
                </span>

                <div class="btn-remove">
                  <a class="remove" href="#">REMOVE</a>
                </div>
              </td>
              <td>
                1
              </td>
              <td>
                $25
              </td>
            </tr>
            </tbody>
          </table>
        </div>
        <div class="form-checkout-wrapper pull-right">
          <div class="form-site-custom">
            <form action="#">
              <fieldset class="form-wrapper">
                <legend><span class="fieldset-legend">Billing Information</span></legend>
                <div class="fieldset-wrapper">
                  <div class="width-form-170">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="First Name" />
                    </div>
                  </div>
                  <div class="width-form-170">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="Last Name" />
                    </div>
                  </div>
                  <div class="width-form-170">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="COMPANY" />
                    </div>
                  </div>
                  <div class="width-form-534">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="ADDRESS" />
                    </div>
                  </div>
                  <div class="width-form-261">

                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="CITY" />
                    </div>
                  </div>
                  <div class="width-form-158">

                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="STATE" />
                    </div>
                  </div>
                  <div class="width-form-91">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="ZIP" />
                    </div>
                  </div>
                  <div class="width-form-261">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="HOME PHONE" />
                    </div>
                  </div>
                  <div class="width-form-261">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="EMAIL" />
                    </div>
                  </div>
                </div>
              </fieldset>
              <fieldset class="form-wrapper">
                <legend><span class="fieldset-legend">Shipping Information</span></legend>
                <div class="fieldset-wrapper">
                  <div class="ff-tt-l clearfix">
                    <div class="form-item form-type-checkbox">
                      <label for="id_checkbox_1">SAME AS BILLING ADDRESS</label>
                      <input class="form-radio" type="checkbox">
                    </div>
                  </div>

                  <div class="width-form-170">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="First Name" />
                    </div>
                  </div>
                  <div class="width-form-170">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="Last Name" />
                    </div>
                  </div>
                  <div class="width-form-170">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="COMPANY" />
                    </div>
                  </div>
                  <div class="width-form-534">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="ADDRESS" />
                    </div>
                  </div>
                  <div class="width-form-261">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="CITY" />
                    </div>
                  </div>
                  <div class="width-form-158">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="STATE" />
                    </div>
                  </div>
                  <div class="width-form-91">
                    <div class="form-item form-type-textfield">
                      <input type="text" class="form-text" placeholder="ZIP" />
                    </div>
                  </div>
                </div>
              </fieldset>
              <fieldset class="form-fieldset">
                <legend><span class="fieldset-legend">Payment Information</span></legend>
                <div class="width-form-138 ff-tt-l">
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
                <div class="width-form-166 ff-tt-l">
                  <div class="form-item">
                    <label>EXPIRATION DATE</label>
                    <input class="form-text" type="text" />
                  </div>
                </div>
                <div class="width-form-100 not-label">
                  <div class="form-item">
                    <input class="form-text" type="text" placeholder="SECURITY CODE" />
                  </div>
                </div>
                <div class="width-form-261 clear-left">
                  <div class="form-item">
                    <input class="form-text" type="text" placeholder="CARD NUMBER" />

                  </div>
                </div>
                <div class="width-form-261">
                  <div class="form-item">
                    <input class="form-text" type="text" placeholder="NAME AS IT APPEARS ON CARD" />
                  </div>
                </div>
              </fieldset>
              <div class="btn-wrapp">
                <div class="btn-submit pull-right">
                  <input type="submit" value="SUBMIT application">
                </div>
              </div>
            </form>
          </div>

        </div>
        <hr>
      </div>
    </div>
  </div>
</div>
<?php include 'src/com/structs/footer/footer.inc'; ?>
</body>
</html>