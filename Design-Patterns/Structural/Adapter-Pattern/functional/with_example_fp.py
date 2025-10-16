"""
with_adapter_fp.py: Demonstrates the Adapter Pattern using a functional
approach with higher-order functions in Python.
"""
import decimal
from typing import Callable

# --- Incompatible Third-Party Services (Adaptees) ---
# These are the functions with interfaces that our system doesn't control.

def stripe_charge(card_details: str, amount_cents: int):
    """Processes a payment in cents via Stripe."""
    amount_dollars = decimal.Decimal(amount_cents) / 100
    print(f"Stripe: Charging card '{card_details}' for ${amount_dollars:.2f}.")

def paypal_send_payment(email: str, amount_dollars: float):
    """Sends a payment in dollars via PayPal."""
    print(f"PayPal: Sending payment of ${amount_dollars:.2f} to '{email}'.")


# --- The Adapter Functions ---
# These are higher-order functions. They take an incompatible function
# and return a new, compatible function that conforms to our target interface.

# Our "Target Interface" is an implicit contract: a function that takes
# a single float argument (the amount in dollars).
PaymentFunction = Callable[[float], None]

def create_stripe_adapter(card_details: str) -> PaymentFunction:
    """
    A higher-order function that acts as an adapter.
    It returns a new function that calls the Stripe API with the correct format.
    """
    def adapter_func(amount: float):
        print("StripeAdapter: Converting amount to cents and calling Stripe API.")
        amount_in_cents = int(amount * 100)
        stripe_charge(card_details, amount_in_cents)
    return adapter_func

def create_paypal_adapter(email: str) -> PaymentFunction:
    """
    A higher-order function that adapts the PayPal API.
    It returns a new function that matches our application's standard interface.
    """
    def adapter_func(amount: float):
        print("PayPalAdapter: Calling PayPal API directly.")
        paypal_send_payment(email, amount)
    return adapter_func


# --- Client Code ---
# The client code interacts with any function that follows the PaymentFunction signature.
# It is completely decoupled from Stripe and PayPal.

def process_order(payment_gateway: PaymentFunction, total_amount: float):
    """
    Processes an order using any compatible payment function.
    This function is simple, clean, and follows the Open/Closed Principle.
    """
    print(f"\n--- Processing an order of ${total_amount:.2f} ---")
    payment_gateway(total_amount)
    print("--- Order processed successfully! ---")


if __name__ == "__main__":
    # Create the adapted functions.
    # In a real app, you would create the appropriate adapter based on user choice.
    stripe_gateway = create_stripe_adapter("1234-5678-9012-3456")
    paypal_gateway = create_paypal_adapter("customer@example.com")

    # Use the client code with the different adapted functions.
    process_order(stripe_gateway, 150.75)
    process_order(paypal_gateway, 89.99)
