package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class Pawn extends Piece {
    
    public Pawn(Colour colour) {
        super(colour, 'P', 1);
    }

    // TODO: getLegalMoves()
    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return null;
    }
}
