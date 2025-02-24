enum Key {
    KEY_NONE = -1,
    KEY_ENTER = '\n',
    KEY_ESCAPE = 27,
    KEY_SPACE = 32,
    KEY_BACKSPACE = 127,
    KEY_TAB = 9,

    // Arrows
    KEY_LEFT = 1000,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
};

enum Effect {
    bold,         // Жирный
    dim,          // Тусклый (бледный)
    italic,       // Курсив
    underline,    // Подчеркивание
    blink,        // Мигающий текст
    reverse,      // Инвертированные цвета (фон <-> текст)
    hidden,       // Скрытый текст
    strikethrough // Зачеркнутый текст
};
