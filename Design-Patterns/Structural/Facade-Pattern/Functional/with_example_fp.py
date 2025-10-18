# --- The Subsystem (as standalone functions) ---

def check_stock(product_id: str, quantity: int) -> tuple[bool, str]:
    """
    Subsystem 1: Checks inventory.
    Returns (success_status, message)
    """
    print(f"Checking stock for {product_id}...")
    if quantity < 100:
        return (True, "Stock is available.")
    else:
        return (False, "Stock is NOT available.")

def process_payment(credit_card: str, amount: float) -> tuple[bool, str]:
    """
    Subsystem 2: Processes payment.
    Returns (success_status, message)
    """
    print(f"Processing payment of ${amount}...")
    if credit_card == "1":
        return (True, "Payment successful !")
    else:
        return (False, "Payment failed (invalid card).")

def create_shipment(product_id: str, address: str) -> tuple[bool, str]:
    """
    Subsystem 3: Creates shipment.
    Returns (success_status, message)
    """
    print(f"Creating shipment for {product_id} to {address}...")
    # This action "succeeds" for the example
    return (True, "Shipment created !.")

# --- The Facade (as a single coordinating function) ---

def place_order(product_id: str, quantity: int, 
                credit_card: str, price: float, 
                address: str) -> bool:
    """
    This is the Facade. It's just a function that calls
    the other functions in the correct order.
    """
    print("--- Initiating order process ---")
    
    # 1. Check stock
    stock_ok, stock_msg = check_stock(product_id, quantity)
    print(stock_msg)  # Print the result from the subsystem
    if not stock_ok:
        print("--- Order process failed (Out of Stock) ---")
        return False

    # 2. Process payment
    amount = price * quantity
    payment_ok, payment_msg = process_payment(credit_card, amount)
    print(payment_msg)
    if not payment_ok:
        print("--- Order process failed (Payment Error) ---")
        return False

    # 3. Create shipment
    ship_ok, ship_msg = create_shipment(product_id, address)
    print(ship_msg)
    if not ship_ok: # Good practice, even if our example always works
        print("--- Order process failed (Shipping Error) ---")
        return False
    
    print("--- Order process completed successfully! ---")
    return True

# --- The Client ---
if __name__ == "__main__":
    
    # The client only needs to know about the facade function
    print("Attempting a valid order...")
    place_order(
        product_id="shampoo", 
        quantity=2, 
        credit_card="1",  # Valid card
        price=50.00, 
        address="21, masr elgdeda, Egypt"
    )

    print("\nAttempting an order with a invalid card...")
    place_order(
        product_id="sokar", 
        quantity=1, 
        credit_card="2",  # Invalid card
        price=150.00, 
        address="456 Oak Ave, Othertown, USA"
    )