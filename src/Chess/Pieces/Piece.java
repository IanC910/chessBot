package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Move;
import Chess.Position;
import Chess.Colour;

public abstract class Piece {

    // Static Piece Store

    public static final Piece NO_PIECE      = new NoPiece();

    public static final Piece WHITE_PAWN    = new Pawn      (Colour.WHITE);
    public static final Piece WHITE_BISHOP  = new Bishop    (Colour.WHITE);
    public static final Piece WHITE_KNIGHT  = new Knight    (Colour.WHITE);
    public static final Piece WHITE_ROOK    = new Rook      (Colour.WHITE);
    public static final Piece WHITE_QUEEN   = new Queen     (Colour.WHITE);
    public static final Piece WHITE_KING    = new King      (Colour.WHITE);

    public static final Piece BLACK_PAWN    = new Pawn      (Colour.BLACK);
    public static final Piece BLACK_BISHOP  = new Bishop    (Colour.BLACK);
    public static final Piece BLACK_KNIGHT  = new Knight    (Colour.BLACK);
    public static final Piece BLACK_ROOK    = new Rook      (Colour.BLACK);
    public static final Piece BLACK_QUEEN   = new Queen     (Colour.BLACK);
    public static final Piece BLACK_KING    = new King      (Colour.BLACK);



    // Non-Static Members

    public final Colour colour;
    public final char symbol;
    public final int value;

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

    public abstract LinkedList<Move> getLegalMoves(Board board, int rank, int file);

    public final LinkedList<Move> getLegalMoves(Board board, Position position) {
        return getLegalMoves(board, position.rank, position.file);
    }
}
