#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm> // For std::find
#include <set>

// For simplicity, we'll represent our JSON as a string.
using JsonString = std::string;

// The UserRole enum remains a good practice.
enum class UserRole {
    AUTHOR,
    EDITOR,
    DEBUGGER
};

// The base interface is still needed.
class ApiResponse {
public:
    virtual ~ApiResponse() = default;
    virtual JsonString generate() const = 0;
};

// --- THE CLASS EXPLOSION BEGINS ---
// Instead of small, reusable decorators, we create a giant class for each combination.

// 1. Base class with no extra data.
class BlogPostResponse : public ApiResponse {
protected:
    int postId;
    // Helper methods to avoid SOME duplication, but the core problem remains.
    JsonString getAuthorData() const {
        return ",\n  \"stats\": {\n"
               "    \"views\": 1024,\n"
               "    \"comments\": 25\n"
               "  }";
    }
    JsonString getEditorData() const {
        return ",\n  \"moderation\": {\n"
               "    \"status\": \"published\",\n"
               "    \"lastEditedBy\": \"editor01\"\n"
               "  }";
    }
    JsonString getDebuggerData() const {
        return ",\n  \"_debug\": {\n"
               "    \"dbQueryMs\": 45,\n"
               "    \"cacheHit\": false,\n"
               "    \"serverNode\": \"prod-us-east-5a\"\n"
               "  }";
    }

public:
    explicit BlogPostResponse(int id) : postId(id) {}

    JsonString generate() const override {
        return "{\n  \"postId\": " + std::to_string(postId) + ",\n" +
               "  \"title\": \"Decorator Pattern in the Real World\",\n" +
               "  \"content\": \"This pattern is great for...\"\n}";
    }
};

// 2. Class for Author ONLY
class BlogPostAuthorResponse : public BlogPostResponse {
public:
    explicit BlogPostAuthorResponse(int id) : BlogPostResponse(id) {}
    JsonString generate() const override {
        JsonString base = BlogPostResponse::generate();
        base.pop_back(); // remove closing brace
        return base + getAuthorData() + "\n}";
    }
};

// 3. Class for Editor ONLY
class BlogPostEditorResponse : public BlogPostResponse {
public:
    explicit BlogPostEditorResponse(int id) : BlogPostResponse(id) {}
    JsonString generate() const override {
        JsonString base = BlogPostResponse::generate();
        base.pop_back();
        return base + getEditorData() + "\n}";
    }
};


// 4. Class for Author AND Editor
// **PROBLEM: Code duplication and rigidity.** We have to explicitly combine the logic.
class BlogPostAuthorEditorResponse : public BlogPostResponse {
public:
    explicit BlogPostAuthorEditorResponse(int id) : BlogPostResponse(id) {}
    JsonString generate() const override {
        JsonString base = BlogPostResponse::generate();
        base.pop_back();
        base += getAuthorData();
        base += getEditorData();
        return base + "\n}";
    }
};

// 5. Class for ALL THREE roles
// **PROBLEM: This gets worse with every new role.**
class BlogPostAllRolesResponse : public BlogPostResponse {
public:
    explicit BlogPostAllRolesResponse(int id) : BlogPostResponse(id) {}
    JsonString generate() const override {
        JsonString base = BlogPostResponse::generate();
        base.pop_back();
        base += getAuthorData();
        base += getEditorData();
        base += getDebuggerData();
        return base + "\n}";
    }
};
// ... And we would still need to create classes for (Debugger), (Author+Debugger), (Editor+Debugger) ...
// This approach is not scalable.

// --- The request handler becomes a complex factory ---
void handleApiRequest(const std::vector<UserRole>& roles) {
    std::cout << "--- New Request ---" << std::endl;
    std::cout << "Context: Request with " << roles.size() << " special role(s)." << std::endl;

    std::unique_ptr<ApiResponse> response;
    
    // Create a set for easier lookup
    std::set<UserRole> roleSet(roles.begin(), roles.end());

    // **PROBLEM: A complex, hard-to-maintain block of conditional logic.**
    bool isAuthor = roleSet.count(UserRole::AUTHOR);
    bool isEditor = roleSet.count(UserRole::EDITOR);
    bool isDebugger = roleSet.count(UserRole::DEBUGGER);

    if (isAuthor && isEditor && isDebugger) {
        response = std::make_unique<BlogPostAllRolesResponse>(101);
    } else if (isAuthor && isEditor) {
        response = std::make_unique<BlogPostAuthorEditorResponse>(101);
    } else if (isAuthor) { // Must check for single roles *after* combinations
        response = std::make_unique<BlogPostAuthorResponse>(101);
    } else if (isEditor) {
        response = std::make_unique<BlogPostEditorResponse>(101);
    } else { // Base case
        response = std::make_unique<BlogPostResponse>(101);
    }
    // This if/else chain is incomplete and already complicated.

    std::cout << "\nFinal JSON Response:\n" << response->generate() << std::endl;
    std::cout << "---------------------\n\n";
}


int main() {
    // Simulate a request from a regular user (no special roles)
    handleApiRequest({});

    // Simulate a request from the post's author
    handleApiRequest({UserRole::AUTHOR});

    // Simulate a request from an editor who is also the author
    handleApiRequest({UserRole::AUTHOR, UserRole::EDITOR});
    
    // Simulate a request for all roles
    handleApiRequest({UserRole::AUTHOR, UserRole::EDITOR, UserRole::DEBUGGER});

    return 0;
}
