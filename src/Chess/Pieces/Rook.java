package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class Rook extends Piece {
    
    public Rook(Colour colour) {
        super(colour, 'R', 5);
    }

    // TODO: getLegalMoves()
    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return null;
    }
    
}
