import json

class UserRole:
    AUTHOR = "AUTHOR"
    EDITOR = "EDITOR"
    DEBUGGER = "DEBUGGER"


def handle_api_request(roles):
    print("--- New Request ---")
    print(f"Context: Request with {len(roles)} special role(s).")

    # Base response
    response = {
        "postId": 101,
        "title": "Decorator Pattern in the Real World",
        "content": "This pattern is great for..."
    }

    # Directly modify based on roles
    if UserRole.AUTHOR in roles:
        response["stats"] = {"views": 1024, "comments": 25}

    if UserRole.EDITOR in roles:
        response["moderation"] = {
            "status": "published",
            "lastEditedBy": "editor01"
        }

    if UserRole.DEBUGGER in roles:
        response["_debug"] = {
            "dbQueryMs": 45,
            "cacheHit": False,
            "serverNode": "prod-us-east-5a"
        }

    print("\nFinal JSON Response:\n", json.dumps(response, indent=2))
    print("---------------------\n")


# --- Simulated requests ---
if __name__ == "__main__":
    handle_api_request([])
    handle_api_request([UserRole.AUTHOR])
    handle_api_request([UserRole.AUTHOR, UserRole.EDITOR])
    handle_api_request([UserRole.EDITOR, UserRole.DEBUGGER])
