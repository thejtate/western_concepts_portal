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
    <div class="sidebar-right">
      <div class="sidebar-item">
        <div class="title-sidebar">
          <h3>Your cart</h3>
        </div>
        <div class="table-check_out">
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
              <td>$44.95</td>
            </tr>
            </tfoot>
            <tbody>
            <tr>
              <td>Sushi Neko t-shirt</td>
              <td>1</td>
              <td> $19.95</td>
            </tr>
            <tr>
              <td>Gift Card</td>
              <td>1</td>
              <td>$25</td>
            </tr>
            </tbody>
          </table>
          <div class="btn-wrapp">
            <div class="btn-submit">
              <a href="#">CHECK OUT</a>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="content-wrapper">
      <div class="content-item">
        <div class="title-content">
          <h3>Store</h3>
        </div>
        <div class="item-product ">
          <figure class="images image-inline">
            <div class="image">
              <a class="product-full" href="images/tmp/_tmp_p-2_big.jpg" >
                <img src="images/tmp/_tmp_p-1.jpg" alt="product" />
              </a>
            </div>
          </figure>
          <div class="content-product">
            <h4>Gift Card</h4>
            <div class="btn-gift">
              <span class="title-btn">HAVE A GIFT CARD?</span>
              <a href="#">Check Your Balance</a>
            </div>
            <div class="form-site-custom">
              <form action="#">
                <div class="width-form-110 ff-tt-l">
                  <div class="form-item">
                    <label>SELECT AMOUNT</label>
                    <select class="form-select">
                      <option value="1">20$</option>
                      <option value="2">40$</option>
                      <option value="3">60$</option>
                      <option value="4">80$</option>
                      <option value="5">100$</option>
                    </select>
                  </div>
                </div>
                <div class="btn-wrapp">
                  <div class="btn-submit">
                    <input type="submit" value="add to cart">
                  </div>
                </div>
              </form>
            </div>
          </div>
        </div>
        <div class="item-product ">
          <figure class="images image-inline">
            <div class="image">
              <a href="images/tmp/_tmp_p-2_big.jpg" class="product-full">
                <img src="images/tmp/_tmp_p-2.jpg" alt="product" />
              </a>
            </div>
          </figure>
          <div class="content-product">
            <h4>Sushi Neko t-shirt</h4>
            <span class="price-product">
              $19.95
            </span>

            <div class="form-site-custom">
              <form action="#">
                <div class="width-form-110 ff-tt-l">
                  <div class="form-item">
                    <label></label>
                    <select class="form-select">
                      <option value="1">S</option>
                      <option value="2">S</option>
                      <option value="3">S</option>
                      <option value="4">S</option>
                      <option value="5">S</option>
                    </select>
                  </div>
                </div>
                <div class="width-form-110 ff-tt-l">
                  <div class="form-item">
                    <label></label>
                    <select class="form-select">
                      <option value="1">GREEN</option>
                      <option value="1">gray</option>
                      <option value="1">red</option>
                      <option value="1">GREEN</option>
                      <option value="1">GREEN</option>
                    </select>
                  </div>
                </div>
                <div class="btn-wrapp clearfix">
                  <div class="btn-submit">
                    <input type="submit" value="add to cart">
                  </div>
                </div>
              </form>
            </div>
          </div>
        </div>
        <div class="item-product ">
          <figure class="images image-inline">
            <div class="image">
              <a href="images/tmp/_tmp_p-2_big.jpg" class="product-full">
                <img src="images/tmp/_tmp_p-3.jpg" alt="product" />
              </a>
            </div>
          </figure>
          <div class="content-product">
            <h4>Musashi’s ballcap</h4>
            <span class="price-product">
              $19.95
            </span>

            <div class="form-site-custom">
              <form action="#">
                <div class="width-form-110 ff-tt-l">
                  <div class="form-item">
                    <label></label>
                    <select class="form-select">
                      <option value="1">S</option>
                      <option value="2">S</option>
                      <option value="3">S</option>
                      <option value="4">S</option>
                      <option value="5">S</option>
                    </select>
                  </div>
                </div>
                <div class="width-form-110 ff-tt-l">
                  <div class="form-item">
                    <label></label>
                    <select class="form-select">
                      <option value="1">GREEN</option>
                      <option value="1">gray</option>
                      <option value="1">red</option>
                      <option value="1">GREEN</option>
                      <option value="1">GREEN</option>
                    </select>
                  </div>
                </div>
                <div class="btn-wrapp clearfix">
                  <div class="btn-submit">
                    <input type="submit" value="add to cart">
                  </div>
                </div>
              </form>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
<?php include 'src/com/structs/footer/footer.inc'; ?>
</body>
</html>