#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm> // For std::find

using namespace std;
// For simplicity, we'll represent our JSON as a string.
// In a real app, you'd use a proper JSON library.
using JsonString = string;

// A more robust way to handle user context instead of booleans
enum class UserRole {
    AUTHOR,
    EDITOR,
    DEBUGGER
};

// 1. The Component Interface
// This is the core interface for any API response we build.
class ApiResponse {
public:
    virtual ~ApiResponse() = default;
    virtual JsonString generate() const = 0;
};

// 2. A Concrete Component
// This is the base response. It fetches and formats the core data.
class BlogPostResponse : public ApiResponse {
private:
    int postId;
public:
    explicit BlogPostResponse(int id) : postId(id) {}

    JsonString generate() const override {
        // In a real app, this would fetch data from a database.
        // For example: SELECT title, content FROM posts WHERE id = postId;
        return "{\n  \"postId\": " + to_string(postId) + ",\n" +
               "  \"title\": \"Decorator Pattern in the Real World\",\n" +
               "  \"content\": \"This pattern is great for...\"\n}";
    }
};

// 3. The Decorator Base Class
// It holds a reference to the response it will decorate.
class ResponseDecorator : public ApiResponse {
protected:
    unique_ptr<ApiResponse> wrappedResponse;
public:
    ResponseDecorator(unique_ptr<ApiResponse> response) : wrappedResponse(move(response)) {}

    JsonString generate() const override {
        return wrappedResponse->generate();
    }
};

// 4. Concrete Decorators
// Each decorator adds a new layer of data to the JSON response.

// Adds view statistics for the post's author.
class AuthorStatsDecorator : public ResponseDecorator {
public:
    AuthorStatsDecorator(unique_ptr<ApiResponse> response) : ResponseDecorator(move(response)) {}

    JsonString generate() const override {
        JsonString baseJson = wrappedResponse->generate();
        // Remove the closing brace to append new data
        baseJson.pop_back(); 
        
        // In a real app, this would fetch stats from a different service or table.
        string statsData = ",\n  \"stats\": {\n"
                            "    \"views\": 1024,\n"
                            "    \"comments\": 25\n"
                            "  }\n}";
        return baseJson + statsData;
    }
};

// Adds moderation info for an editor.
class EditorModerationDecorator : public ResponseDecorator {
public:
    EditorModerationDecorator(unique_ptr<ApiResponse> response) : ResponseDecorator(move(response)) {}

    JsonString generate() const override {
        JsonString baseJson = wrappedResponse->generate();
        baseJson.pop_back();

        string moderationData = ",\n  \"moderation\": {\n"
                                     "    \"status\": \"published\",\n"
                                     "    \"lastEditedBy\": \"editor01\"\n"
                                     "  }\n}";
        return baseJson + moderationData;
    }
};

// Adds debug/profiling info for a developer.
class DebugProfilingDecorator : public ResponseDecorator {
public:
    DebugProfilingDecorator(unique_ptr<ApiResponse> response) : ResponseDecorator(move(response)) {}

    JsonString generate() const override {
        JsonString baseJson = wrappedResponse->generate();
        baseJson.pop_back();

        string profilingData = ",\n  \"_debug\": {\n"
                                    "    \"dbQueryMs\": 45,\n"
                                    "    \"cacheHit\": false,\n"
                                    "    \"serverNode\": \"prod-us-east-5a\"\n"
                                    "  }\n}";
        return baseJson + profilingData;
    }
};

// --- Web Server Request Handler Simulation ---
// Refactored to accept a vector of roles instead of multiple booleans.
void handleApiRequest(const vector<UserRole>& roles) {
    cout << "--- New Request ---" << endl;
    cout << "Context: Request with " << roles.size() << " special role(s)." << endl;

    // Start with the basic blog post response
    unique_ptr<ApiResponse> response = make_unique<BlogPostResponse>(101);

    // Conditionally wrap the response with decorators by checking the roles vector
    if (find(roles.begin(), roles.end(), UserRole::AUTHOR) != roles.end()) {
        response = make_unique<AuthorStatsDecorator>(move(response));
    }
    if (find(roles.begin(), roles.end(), UserRole::EDITOR) != roles.end()) {
        response = make_unique<EditorModerationDecorator>(move(response));
    }
    if (find(roles.begin(), roles.end(), UserRole::DEBUGGER) != roles.end()) {
        response = make_unique<DebugProfilingDecorator>(move(response));
    }

    cout << "\nFinal JSON Response:\n" << response->generate() << endl;
    cout << "---------------------\n\n";
}

int main() {
    // Simulate a request from a regular user (no special roles)
    handleApiRequest({});

    // Simulate a request from the post's author
    handleApiRequest({UserRole::AUTHOR});

    // Simulate a request from an editor who is also the author
    handleApiRequest({UserRole::AUTHOR, UserRole::EDITOR});
    
    // Simulate a request from a developer debugging an editor's view
    handleApiRequest({UserRole::EDITOR, UserRole::DEBUGGER});

    return 0;
}

