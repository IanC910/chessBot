package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class NoPiece extends Piece {
    
    public NoPiece() {
        super(Colour.NONE, ' ', 0);
    }

    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return new LinkedList<Position>();
    }
    
}
