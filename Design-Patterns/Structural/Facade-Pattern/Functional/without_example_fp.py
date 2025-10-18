# --- The Subsystem (as standalone functions) ---
# (These are the same as above)

def check_stock(product_id: str, quantity: int) -> tuple[bool, str]:
    print(f"Checking stock for {product_id}...")
    if quantity < 100:
        return (True, "Stock is available.")
    else:
        return (False, "Stock is NOT available.")

def process_payment(credit_card: str, amount: float) -> tuple[bool, str]:
    print(f"Processing payment of ${amount}...")
    if credit_card == "1":
        return (True, "Payment successful !")
    else:
        return (False, "Payment failed (invalid card).")

def create_shipment(product_id: str, address: str) -> tuple[bool, str]:
    print(f"Creating shipment for {product_id} to {address}...")
    return (True, "Shipment created !.")


# --- The Client ---
if __name__ == "__main__":
    
    # --- Use Case 1: Successful Order ---
    print("Attempting a valid order...")
    
    # --- All this logic was previously hidden inside the Facade ---
    # The client must now know everything:
    
    # Define order details
    product_id_1 = "shampoo"
    quantity_1 = 2
    credit_card_1 = "1"  # Valid card
    price_1 = 50.00
    address_1 = "21, masr elgdeda, Egypt"

    print("--- Initiating order process ---")
    
    # 1. Client must call check_stock
    stock_ok, stock_msg = check_stock(product_id_1, quantity_1)
    print(stock_msg)
    
    if stock_ok:
        # 2. Client must call process_payment
        amount_1 = price_1 * quantity_1
        payment_ok, payment_msg = process_payment(credit_card_1, amount_1)
        print(payment_msg)
        
        if payment_ok:
            # 3. Client must call create_shipment
            ship_ok, ship_msg = create_shipment(product_id_1, address_1)
            print(ship_msg)
            print("--- Order process completed successfully! ---")
        else:
            print("--- Order process failed (Payment Error) ---")
    else:
        print("--- Order process failed (Out of Stock) ---")
    # --- End of logic for Use Case 1 ---


    # --- Use Case 2: Failed Order (Payment) ---
    print("\nAttempting an order with a invalid card...")
    
    # --- The client must REPEAT all the complex logic ---
    
    # Define order details
    product_id_2 = "sokar"
    quantity_2 = 1
    credit_card_2 = "2"  # Invalid card
    price_2 = 150.00
    address_2 = "456 Oak Ave, Othertown, USA"

    print("--- Initiating order process ---")
    
    # 1. Client must call check_stock again
    stock_ok, stock_msg = check_stock(product_id_2, quantity_2)
    print(stock_msg)
    
    if stock_ok:
        # 2. Client must call process_payment again
        amount_2 = price_2 * quantity_2
        payment_ok, payment_msg = process_payment(credit_card_2, amount_2)
        print(payment_msg)

        if payment_ok:
            # 3. Client must call create_shipment again
            ship_ok, ship_msg = create_shipment(product_id_2, address_2)
            print(ship_msg)
            print("--- Order process completed successfully! ---")
        else:
            print("--- Order process failed (Payment Error) ---")
    else:
        print("--- Order process failed (Out of Stock) ---")
    # --- End of logic for Use Case 2 ---