#include "tests_checking.h"
#include <deque>
#include <iostream>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction> &student_actions,
                                       const std::vector<size_t> &queries) {
    std::deque<std::string> dq;
    size_t actions_count = student_actions.size();

    for (StudentAction action : student_actions) {
        if (action.side == Side::Top) {
            dq.push_back(action.name);
        } else {
            dq.push_front(action.name);
        }
    }
    std::vector<std::string> names;
    for (size_t num : queries) {
        names.push_back(dq.at(actions_count - num));
    }

    return names;
}