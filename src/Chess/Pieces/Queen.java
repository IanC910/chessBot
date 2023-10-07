package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class Queen extends Piece {
    
    public Queen(Colour colour) {
        super(colour, 'Q', 9);
    }

    // TODO: getLegalMoves()
    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return null;
    }
    
}
