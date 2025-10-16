"""
without_example_fp.py: Demonstrates a tightly-coupled approach to handling
different payment APIs in a functional style, without the Adapter Pattern.
"""
import decimal

# --- Incompatible Third-Party Services (Adaptees) ---
# These are the functions with interfaces that our system doesn't control.

def stripe_charge(card_details: str, amount_cents: int):
    """Processes a payment in cents via Stripe."""
    amount_dollars = decimal.Decimal(amount_cents) / 100
    print(f"Stripe: Charging card '{card_details}' for ${amount_dollars:.2f}.")

def paypal_send_payment(email: str, amount_dollars: float):
    """Sends a payment in dollars via PayPal."""
    print(f"PayPal: Sending payment of ${amount_dollars:.2f} to '{email}'.")

# --- Client Code ---
# This client code is tightly coupled to the specific payment providers.

def process_order(provider: str, amount: float, user_details: dict):
    """
    Processes an order, but contains messy, coupled logic to handle
    different payment providers.

    This function violates the Open/Closed Principle. To add a new
    payment provider, this function MUST be modified.
    """
    print(f"\n--- Processing an order of ${amount:.2f} ---")
    
    if provider == "stripe":
        print("Client: Converting amount to cents for Stripe.")
        amount_in_cents = int(amount * 100)
        stripe_charge(user_details["card"], amount_in_cents)
        
    elif provider == "paypal":
        print("Client: Calling PayPal directly.")
        paypal_send_payment(user_details["email"], amount)
        
    else:
        print(f"Error: Unknown payment provider '{provider}'.")
        return

    print("--- Order processed successfully! ---")


if __name__ == "__main__":
    # For a real app, this data would come from the user's order.
    stripe_user_details = {"card": "1234-5678-9012-3456"}
    paypal_user_details = {"email": "customer@example.com"}

    # The client code must know the specific details for each provider.
    process_order("stripe", 150.75, stripe_user_details)
    process_order("paypal", 89.99, paypal_user_details)
