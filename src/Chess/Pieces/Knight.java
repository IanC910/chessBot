package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class Knight extends Piece {
    
    public Knight(Colour colour) {
        super(colour, 'N', 3);
    }

    // TODO: getLegalMoves()
    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return null;
    }
    
}
