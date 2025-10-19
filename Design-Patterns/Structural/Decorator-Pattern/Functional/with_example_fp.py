import json

# --- 1. The base response function ---
def blog_post_response(post_id: int):
    def generate():
        return {
            "postId": post_id,
            "title": "Decorator Pattern in the Real World",
            "content": "This pattern is great for..."
        }
    return generate


# --- 2. Decorators implemented as higher-order functions ---
def author_stats_decorator(response_func):
    def generate():
        data = response_func()
        data["stats"] = {"views": 1024, "comments": 25}
        return data
    return generate


def editor_moderation_decorator(response_func):
    def generate():
        data = response_func()
        data["moderation"] = {
            "status": "published",
            "lastEditedBy": "editor01"
        }
        return data
    return generate


def debug_profiling_decorator(response_func):
    def generate():
        data = response_func()
        data["_debug"] = {
            "dbQueryMs": 45,
            "cacheHit": False,
            "serverNode": "prod-us-east-5a"
        }
        return data
    return generate


# --- 3. User roles (like enum) ---
class UserRole:
    AUTHOR = "AUTHOR"
    EDITOR = "EDITOR"
    DEBUGGER = "DEBUGGER"


# --- 4. API request handler ---
def handle_api_request(roles):
    print("--- New Request ---")
    print(f"Context: Request with {len(roles)} special role(s).")

    # Start with base generator
    response_func = blog_post_response(101)

    # Dynamically wrap using decorators
    if UserRole.AUTHOR in roles:
        response_func = author_stats_decorator(response_func)
    if UserRole.EDITOR in roles:
        response_func = editor_moderation_decorator(response_func)
    if UserRole.DEBUGGER in roles:
        response_func = debug_profiling_decorator(response_func)

    # Execute final composed function
    response_json = response_func()
    print("\nFinal JSON Response:\n", json.dumps(response_json, indent=2))
    print("---------------------\n")


# --- 5. Simulated requests ---
if __name__ == "__main__":
    handle_api_request([])
    handle_api_request([UserRole.AUTHOR])
    handle_api_request([UserRole.AUTHOR, UserRole.EDITOR])
    handle_api_request([UserRole.EDITOR, UserRole.DEBUGGER])
