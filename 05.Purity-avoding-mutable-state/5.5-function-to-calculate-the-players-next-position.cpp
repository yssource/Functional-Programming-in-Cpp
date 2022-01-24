enum direction_t {
  Left,
  Right,
  Up,
  Down
};

class position_t {
public:
  position_t(position_t const& original, direction_t direction);

  int x;
  int y;
};

class maze_t {
public:
  auto is_wall(position_t) const -> bool;
};

auto next_position(direction_t direction, position_t const& previous_position, maze_t const& maze)
  -> position_t {
  // Calculates the desired position even if it might be a wall
  position_t const desired_position{ previous_position, direction };

  // If the new position isn't a wall, returns it;
  // otherwise, returns the old position
  return maze.is_wall(desired_position) ? previous_position
                                        : desired_position;   
}
