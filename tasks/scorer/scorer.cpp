#include "scorer.h"

bool Comp(const Event* a, const Event* b) {
    return a->time < b->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable passed_tasks;
    ScoreTable failed_tasks;
    std::set<StudentName> names;

    std::vector<const Event*> events_copies;
    for (const Event& ev : events) {
        events_copies.push_back(&ev);
    }

    std::sort(events_copies.begin(), events_copies.end(), Comp);

    for (const Event* ev : events_copies) {
        if (ev->time <= score_time) {
            names.insert(ev->student_name);
            if (ev->event_type == EventType::CheckSuccess) {
                passed_tasks[ev->student_name].insert(ev->task_name);
            }
            if (ev->event_type == EventType::MergeRequestOpen) {
                failed_tasks[ev->student_name].insert(ev->task_name);
            }
            if (ev->event_type == EventType::MergeRequestClosed) {
                failed_tasks[ev->student_name].erase(ev->task_name);
            }
            if (ev->event_type == EventType::CheckFailed) {
                passed_tasks[ev->student_name].erase(ev->task_name);
            }
        }
    }

    ScoreTable passed_tasks_buf;
    for (StudentName name : names) {
        for (TaskName task_name : passed_tasks[name]) {
            if (failed_tasks[name].find(task_name) == failed_tasks[name].end()) {
                passed_tasks_buf[name].insert(task_name);
            }
        }
    }

    return passed_tasks_buf;
}