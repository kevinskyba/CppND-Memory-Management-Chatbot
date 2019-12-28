#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <memory>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    // NOTE:: Since we want to own this resource we keep a shared_ptr on it.
    // We are not using unique_ptr since in case of copying this class sharing the same _image is a good way to
    // save resources, since we are not manipulating it.
    std::shared_ptr<wxBitmap> _image; // avatar image

    // data handles (not owned)
    // NOTE: I keep these raw pointers since making them weak_ptr would just limit the reusability of this class.
    // This should be fine since we don't want to manipulate lifetime. (R.30)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    //// STUDENT CODE
    ////

    // I define that ChatBot is not copyable because ChatLogic is not
    ChatBot(const ChatBot& other) = delete; // copy constructor

    ChatBot(ChatBot&& other) noexcept; // move constructor
    ChatBot &operator=(const ChatBot& other); // copy assigment
    ChatBot &operator=(ChatBot&& other) noexcept; // move assigment

    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image.get(); }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */