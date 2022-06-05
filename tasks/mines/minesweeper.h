#pragma once

#include <string>
#include <vector>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    struct CellStatus {
        bool opened = false;
        bool flag = false;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    const int dx_[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy_[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

    std::vector<std::vector<int8_t> > field_;
    std::vector<std::vector<CellStatus> > field_status_;
    GameStatus current_status_;
    size_t n_, m_, mines_, count_opened_;

    time_t start_game_time_;
    time_t end_game_time_;

    void Initialize();
    void RandomizeMines();
    void AddBomb(size_t pos_x, size_t pos_y);
    bool IsValid(size_t pos_x, size_t pos_y);
};
