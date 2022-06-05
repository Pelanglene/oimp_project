#include "minesweeper.h"

#include <numeric>
#include <random>
#include <ctime>
#include <queue>

#include <iostream>

const int8_t EMPTY = 0;
const int8_t BOMB = 9;

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    m_ = height;
    n_ = width;
    mines_ = mines_count;
    count_opened_ = 0;
    Initialize();
    RandomizeMines();
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    m_ = height;
    n_ = width;
    mines_ = cells_with_mines.size();
    count_opened_ = 0;
    Initialize();
    for (const auto& u : cells_with_mines) {
        AddBomb(u.x, u.y);
    }
}
/// ------------------------------------------------- ///

void Minesweeper::OpenCell(const Cell& cell) {
    switch (current_status_) {
        case GameStatus::NOT_STARTED:
            current_status_ = GameStatus::IN_PROGRESS;
            start_game_time_ = time(nullptr);
            break;
        case GameStatus::DEFEAT:
            return;
        case GameStatus::VICTORY:
            return;
        default:
            break;
    }

    if (field_status_[cell.x][cell.y].flag) {
        return;
    }

    if (!field_status_[cell.x][cell.y].opened) {
        if (field_[cell.x][cell.y] == BOMB) {
            end_game_time_ = time(nullptr);
            current_status_ = GameStatus::DEFEAT;
        }
        std::queue<Cell> q;
        q.push(Cell{cell.x, cell.y});

        while (!q.empty()) {
            Cell curr_cell = q.front();
            q.pop();
            if (field_status_[curr_cell.x][curr_cell.y].opened) {
                continue;
            }
            ++count_opened_;
            field_status_[curr_cell.x][curr_cell.y].opened = true;
            if (EMPTY == field_[curr_cell.x][curr_cell.y]) {
                for (size_t i = 0; i < 8; ++i) {
                    int bx = curr_cell.x + dx_[i];
                    int by = curr_cell.y + dy_[i];
                    if (IsValid(bx, by) && !field_status_[bx][by].opened && !field_status_[bx][by].flag) {
                        q.push(Cell{static_cast<size_t>(bx), static_cast<size_t>(by)});
                    }
                }
            }
        }
    }

    /// CHECK END GAME ///

    if (current_status_ == GameStatus::DEFEAT) {
        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                field_status_[i][j].opened = true;
                field_status_[i][j].flag = false;
            }
        }
        return;
    }
    if (count_opened_ + mines_ == n_ * m_) {
        current_status_ = GameStatus::VICTORY;
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (current_status_ == GameStatus::DEFEAT || current_status_ == GameStatus::VICTORY) {
        return;
    }

    field_status_[cell.x][cell.y].flag ^= 1;
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return current_status_;
}

time_t Minesweeper::GetGameTime() const {
    if (current_status_ == GameStatus::NOT_STARTED) {
        return 0;
    }
    if (current_status_ == GameStatus::IN_PROGRESS) {
        return time(nullptr) - start_game_time_;
    }
    return end_game_time_ - start_game_time_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField ans(m_);
    for (auto& u : ans) {
        u.resize(n_);
    }

    for (size_t i = 0; i < m_; ++i) {
        for (size_t j = 0; j < n_; ++j) {
            if (field_status_[j][i].flag) {
                ans[i][j] = '?';
                continue;
            }
            if (!field_status_[j][i].opened) {
                ans[i][j] = '-';
                continue;
            }
            if (field_[j][i] == EMPTY) {
                ans[i][j] = '.';
            } else if (field_[j][i] == BOMB) {
                ans[i][j] = '*';
            } else {
                ans[i][j] = field_[j][i] + '0';
            }
        }
    }
    return ans;
}

/// ------------------------------------------------- ///

void Minesweeper::Initialize() {
    field_.clear();
    field_status_.clear();
    field_.resize(n_);
    for (auto& u : field_) {
        u.resize(m_, EMPTY);
    }
    field_status_.resize(n_);
    for (auto& u : field_status_) {
        u.resize(m_);
    }
    current_status_ = GameStatus::NOT_STARTED;
}

void Minesweeper::RandomizeMines() {
    std::vector<int> mines_positions(n_ * m_);
    std::iota(mines_positions.begin(), mines_positions.end(), 0);

    std::mt19937 rnd(time(nullptr));
    for (size_t i = 0; i < mines_; ++i) {
        int pos = rnd() % mines_positions.size();
        std::swap(mines_positions[pos], mines_positions.back());
        AddBomb(mines_positions.back() / m_, mines_positions.back() % m_);
        mines_positions.pop_back();
    }
}

bool Minesweeper::IsValid(size_t pos_x, size_t pos_y) {
    return (pos_x >= 0 && pos_x < n_ && pos_y >= 0 && pos_y < m_);
}

void Minesweeper::AddBomb(size_t pos_x, size_t pos_y) {
    field_[pos_x][pos_y] = BOMB;
    for (size_t i = 0; i < 8; ++i) {
        int bx = pos_x + dx_[i];
        int by = pos_y + dy_[i];
        if (IsValid(bx, by) && EMPTY <= field_[bx][by] && field_[bx][by] < BOMB) {
            ++field_[bx][by];
        }
    }
}