package Chess;

public class Piece {

    public enum Colour {
        WHITE ('w'),
        BLACK ('b');

        public final char symbol;

        Colour(char symbol) {
            this.symbol = symbol;
        }
    };

    public enum Type {
        PAWN    ('P', 1),
        BISHOP  ('B', 3),
        KNIGHT  ('N', 3),
        ROOK    ('R', 5),
        QUEEN   ('Q', 9),
        KING    ('K', 0);

        public final char symbol;
        public final int value;

        Type(char symbol, int value) {
            this.symbol = symbol;
            this.value = value;
        }
    };
    
    public final Colour colour;
    public final Type type;

    public Piece(Colour colour, Type type) {
        this.colour = colour;
        this.type = type;
    }

    public String getSymbol() {
        return "" + colour.symbol + type.symbol;
    }
}
