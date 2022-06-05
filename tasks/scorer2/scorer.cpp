#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    mp_[student_name][task_name].CI_passed = false;
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    mp_[student_name][task_name].CI_passed = true;
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    mp_[student_name][task_name].MR_opened = true;
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    mp_[student_name][task_name].MR_opened = false;
}

void Scorer::Reset() {
    mp_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable ans;
    for (auto& student : mp_) {
        for (auto& task : student.second) {
            if (task.second.CI_passed && !task.second.MR_opened) {
                ans[student.first].insert(task.first);
            }
        }
    }
    return ans;
}