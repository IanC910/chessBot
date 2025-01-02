package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Colour;
import Chess.Move;

public class NoPiece extends Piece {
    
    public NoPiece() {
        super(Colour.NONE, ' ', 0);
    }

    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        return new LinkedList<Move>();
    }
}
