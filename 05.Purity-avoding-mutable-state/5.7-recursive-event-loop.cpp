enum direction_t {
  Left,
  Right,
  Up,
  Down
};

class position_t {
public:
  position_t(position_t const& original, direction_t direction);

  int const x;
  int const y;
};

class maze_t {
public:
  maze_t(char const*);

  auto start_position() const -> position_t;
  auto is_wall(position_t const&) const -> bool;
  auto is_exit(position_t const&) const -> bool;
};

auto draw_maze() -> void;
auto draw_player(position_t const& position, direction_t direction) -> void;

auto next_position(direction_t direction, position_t const& previous_position, maze_t const& maze)
  -> position_t {
  position_t const desired_position{ previous_position, direction };
 
  return maze.is_wall(desired_position) ? previous_position
                                        : desired_position;   
}

position_t::position_t(position_t const& original, direction_t direction)
  : x{ direction == Left  ? original.x - 1 :
       direction == Right ? original.x + 1 :
                            original.x     }
  , y{ direction == Up    ? original.y + 1 :
       direction == Down  ? original.y - 1 :
                            original.y     } {}

auto process_events(maze_t const& maze, position_t const& current_position) -> void {
  if (maze.is_exit(current_position)) {
    // show message and exit
    return;
  }

  // Calculates the direction based on user input
  direction_t const direction{ /* ... */ };
  
  // Shows the maze and the player
  draw_maze();
  draw_player(current_position, direction);

  // Gets the new position
  auto const new_position{ next_position(direction, current_position, maze) };

  // Continues processing the events, but now with the player moved to the new
  // cell
  process_events(maze, new_position);
}

// The main function only needs to load the maze and call process_events with
// the player's initial position.
auto main() -> int {
  maze_t const maze{ "maze.data" };
  process_events(maze, maze.start_position());
}
