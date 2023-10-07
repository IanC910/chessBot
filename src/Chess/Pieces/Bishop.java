package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class Bishop extends Piece {
    
    public Bishop(Colour colour) {
        super(colour, 'B', 3);
    }

    // TODO: getLegalMoves()
    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return null;
    }
    
}
