<?php $title = 'Store'; ?>
<?php include 'tpl/includes/head.inc'; ?>
<body class="page-store page">
<div class="outer-wrapper">
	<?php include 'tpl/layout/header.inc'; ?>
	<div class="inner-wrapper">
		<div class="content-wrapper">
			<div class="content-item">
				<div class="content-title">
					<h1>Store</h1>
				</div>
				<div class="item-product">
					<figure>
						<div class="img">
							<img src="theme/images/tmp/tmp-p-1.jpg" alt="">
						</div>
						<figcaption>
							<h4>Gift Card</h4>
							<div class="form form-product">
								<div class="form-field-select form-field">
									<div class="form-item form-type-select">
										<label>SELECT AMOUNT</label>
										<select class="form-select">
											<option>$20</option>
											<option>$40</option>
											<option>$60</option>
											<option>$80</option>
											<option>$100</option>
										</select>
									</div>
								</div>
								<div class="btn-submit">
									<input type="submit" value="add to cart" class="form-submit">
								</div>
							</div>
						</figcaption>
					</figure>
					<div class="btn-gift">
						<span class="btn-title">HAVE A GIFT CARD?</span>
						<a href="#">Check Your Balance</a>
					</div>
				</div>
				<div class="item-product">
					<figure>
						<div class="img">
							<img src="theme/images/tmp/tmp-p-2.jpg" alt="">
						</div>
						<figcaption>
							<h4>Sushi Neko t-shirt</h4>
              <span class="price-product">$19.95</span>
							<div class="form form-product">
								<div class="form-field-select form-field">
									<div class="form-item form-type-select">
										<label>Size</label>
										<select class="form-select">
											<option>s</option>
											<option>m</option>
											<option>xl</option>
											<option>xxl</option>
										</select>
									</div>
								</div>
								<div class="form-field-select form-field">
									<div class="form-item form-type-select">
										<label>Color</label>
										<select class="form-select">
											<option>green</option>
											<option>blue</option>
											<option>red</option>
											<option>orange</option>
										</select>
									</div>
								</div>
                <div class="btn-wrapper">
                  <div class="btn-submit">
                    <input type="submit" value="add to cart" class="form-submit">
                  </div>
                </div>
							</div>
						</figcaption>
					</figure>
				</div>
				<div class="item-product">
					<figure>
						<div class="img">
							<img src="theme/images/tmp/tmp-p-3.jpg" alt="">
						</div>
						<figcaption>
							<h4>Musashi’s ballcap</h4>
							<span class="price-product">$16.95</span>
							<div class="form form-product">
								<div class="form-field-select form-field">
									<div class="form-item form-type-select">
										<label>Size</label>
										<select class="form-select">
											<option>s</option>
											<option>m</option>
											<option>xl</option>
											<option>xxl</option>
										</select>
									</div>
								</div>
								<div class="form-field-select form-field">
									<div class="form-item form-type-select">
										<label>Color</label>
										<select class="form-select">
											<option>black</option>
											<option>blue</option>
											<option>red</option>
											<option>orange</option>
										</select>
									</div>
								</div>
								<div class="btn-wrapper">
									<div class="btn-submit">
										<input type="submit" value="add to cart" class="form-submit">
									</div>
								</div>
							</div>
						</figcaption>
					</figure>
				</div>
			</div>
			<div class="cart-wrapper wrapper-drop-down collapsed">
				<div class="btn-dd-wrapper">
					<a class="btn-dd" href="#">View Cart</a>
				</div>
				<div class="box-drop-down form form-cart">
					<table class="table">
						<thead>
						<tr>
							<th></th>
							<th class="item">ITEM</th>
							<th class="qty">QTY</th>
							<th class="price">PRICE</th>
						</tr>
						</thead>
						<tbody>
						<tr>
							<td><a href="#" class="btn-remove"></a></td>
							<td class="item">Sushi Neko t-shirt</td>
							<td class="qty">1</td>
							<td class="price">$19.95</td>
						</tr>
						<tr>
							<td><a href="#" class="btn-remove"></a></td>
							<td class="item">Sushi Neko t-shirt</td>
							<td class="qty">1</td>
							<td class="price">$19.95</td>
						</tr>
						</tbody>
						<tfoot>
						<tr>
							<td colspan="3" class="qty">SUB-TOTAL</td>
							<td class="price">$19.95</td>
						</tr>
						</tfoot>
					</table>
					<div class="btn-wrapper">
						<div class="btn-submit">
              <a href="#">Checkout</a>
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
</div>
</body>
</html>