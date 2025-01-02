package Chess;

public enum Colour {
    NONE  (' ', 0),
    WHITE ('w', 0),
    BLACK ('b', 1);

    public final char symbol;
    public final int value;

    Colour(char symbol, int value) {
        this.symbol = symbol;
        this.value = value;
    }

    public Colour getOther() {
        if(this == NONE) {
            return NONE;
        }
        else if(this == WHITE) {
            return BLACK;
        }
        return WHITE;
    }
};
