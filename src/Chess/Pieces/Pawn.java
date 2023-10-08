package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Move;

public class Pawn extends Piece {
    
    public Pawn(Colour colour) {
        super(colour, 'P', 1);
    }

    // TODO: getLegalMoves()
    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        LinkedList<Move> legalMoves = new LinkedList<>();

        Move move = new Move(
            rank,
            file,
            rank + Board.FORWARD_DIR[this.colour.value],
            file
        );

        if(!move.doesCheckOwnKing(board)) {
            legalMoves.add(move);
        }

        return legalMoves;
    }
}
