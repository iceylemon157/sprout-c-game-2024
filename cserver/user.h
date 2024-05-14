#include <vector>

class UserAction {
public:
    UserAction() {
        Initialize();
    }
    void SendOperation(ctl::GameController&);
    void GetEvents(std::vector<std::string> events);
    void ReceiveEvents(ctl::GameController&, std::vector<std::string>);

    void InitGame(ctl::GameController&);

private:
    void Initialize();
};
