package Chess;

import java.util.LinkedList;

public abstract class Piece {

    public enum Colour {
        NONE  (' '),
        WHITE ('w'),
        BLACK ('b');

        public final char symbol;

        Colour(char symbol) {
            this.symbol = symbol;
        }
    };

    public final Colour colour;
    public final char symbol;
    public final int value;
    
    // public static final Piece NO_PIECE = new NullPiece();

    // public static final Piece WHITE_PAWN = new Pawn(Colour.WHITE);
    // public static final Piece BLACK_PAWN = new Pawn(Colour.BLACK);

    // TODO static constants for each piece (maybe in Piece Catalogue)

    public Piece(Colour colour, char symbol, int value) {
        this.colour = colour;
        this.symbol = symbol;
        this.value = value;
    }

    public String getSymbol() {
        return "" + colour.symbol + this.symbol;
    }

    public boolean equals(Piece piece) {
        return (this.colour == piece.colour && this.symbol == piece.symbol);
    }

    public abstract LinkedList<Position> getLegalMoves(Board board, Position position);
}
