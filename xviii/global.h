#pragma once

const unsigned int xResolution{1360};
const unsigned int yResolution{768};

using FrameTime = float;

constexpr FrameTime ftSlice{1.f};
constexpr FrameTime ftStep{1.f};

const std::string SUCCESSFUL_ROTATION{"Successfully rotated to "};
const std::string ALREADY_ATTACKED{"Cannot attack any more"};
const std::string ALREADY_FACING{"Already facing "};
const std::string ALREADY_ROTATED{"Already rotated this turn"};
const std::string NO_MOV{"Invalid move order: not enough mov"};
const std::string NO_ROTATE_AFTER_MELEE{"Cannot rotate after melee attacking"};
const std::string NO_ROTATE_AFTER_ATTACK{"Cannot rotate after attacking"};
const std::string OBSTRUCTION_PRESENT_MOV{"Invalid move order: line of sight not clear"};
const std::string OBSTRUCTION_PRESENT_ATK{"Invalid attack order: line of sight not clear"};
const std::string INVALID_DIR_MOV{"Invalid move order: hrzntl or wrong dir"};
const std::string INVALID_DIR_ATK{"Invalid attack order: hrzntl or wrong dir"};
const std::string CANNOT_HEAL_SELF{"Cannot heal self"};
const std::string ALREADY_HEALED{"Already healed"};
const std::string AT_MAX_HP{"Unit is at max HP"};
const std::string HEAL_SUCCESS{"Successfully healed for "};
const std::string MOV_SUCCESS{"Successfully moved to: "};
const std::string OUT_OF_RANGE{"Out of max range: "};

const sf::Keyboard::Key DELETE_KEY = sf::Keyboard::Delete;

const sf::Keyboard::Key RANDOMNATION_KEY = sf::Keyboard::R;

const sf::Keyboard::Key UP_KEY = sf::Keyboard::W;
const sf::Keyboard::Key DOWN_KEY = sf::Keyboard::S;
const sf::Keyboard::Key LEFT_KEY = sf::Keyboard::A;
const sf::Keyboard::Key RIGHT_KEY = sf::Keyboard::D;

const sf::Keyboard::Key RESETZOOM_KEY = sf::Keyboard::R;
const sf::Keyboard::Key ZOOMOUT_KEY = sf::Keyboard::Dash;
const sf::Keyboard::Key ZOOMIN_KEY = sf::Keyboard::Equal;

const sf::Keyboard::Key HIDE_UI_KEY = sf::Keyboard::H;

const sf::Keyboard::Key SPAWNINF_KEY = sf::Keyboard::T;
const sf::Keyboard::Key SPAWNCAV_KEY = sf::Keyboard::Y;
const sf::Keyboard::Key SPAWNART_KEY = sf::Keyboard::F;
const sf::Keyboard::Key SPAWNMOR_KEY = sf::Keyboard::G;
const sf::Keyboard::Key SPAWNGEN_KEY = sf::Keyboard::U;

const sf::Keyboard::Key NORTH_KEY = sf::Keyboard::Up;
const sf::Keyboard::Key EAST_KEY = sf::Keyboard::Right;
const sf::Keyboard::Key SOUTH_KEY = sf::Keyboard::Down;
const sf::Keyboard::Key WEST_KEY = sf::Keyboard::Left;

const sf::Keyboard::Key CONFIRM_KEY = sf::Keyboard::Return;

const sf::Keyboard::Key UP_ARROW = sf::Keyboard::Up;
const sf::Keyboard::Key DOWN_ARROW = sf::Keyboard::Down;
const sf::Keyboard::Key RIGHT_ARROW = sf::Keyboard::Right;
const sf::Keyboard::Key LEFT_ARROW = sf::Keyboard::Left;

const sf::Keyboard::Key TOGGLE_SAVE = sf::Keyboard::Z;

const sf::Keyboard::Key ONE_KEY = sf::Keyboard::Num1;
const sf::Keyboard::Key TWO_KEY = sf::Keyboard::Num2;
const sf::Keyboard::Key THREE_KEY = sf::Keyboard::Num3;
const sf::Keyboard::Key FOUR_KEY = sf::Keyboard::Num4;
const sf::Keyboard::Key FIVE_KEY = sf::Keyboard::Num5;
const sf::Keyboard::Key SIX_KEY = sf::Keyboard::Num6;
const sf::Keyboard::Key SEVEN_KEY = sf::Keyboard::Num7;
const sf::Keyboard::Key EIGHT_KEY = sf::Keyboard::Num8;
const sf::Keyboard::Key NINE_KEY = sf::Keyboard::Num9;