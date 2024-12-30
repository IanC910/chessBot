package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Colour;
import Chess.Move;
import Chess.Position;

public class Pawn extends Piece {
    
    public Pawn(Colour colour) {
        super(colour, 'P', 1);
    }

    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        LinkedList<Move> legalMoves = new LinkedList<>();

        Position startPos = new Position(rank, file);
        
        // Non attacking move
        Position endPos = new Position(
            rank + Board.FORWARD_DIR[this.colour.value],
            file
        );

        Move move = new Move(startPos, this, endPos);

        if(Position.isValid(endPos) &&
            !move.checksOwnKing(board) &&
            board.getPiece(endPos).equals(Piece.NO_PIECE)
        ) {
            legalMoves.add(move);
        }

        // Left attacking move
        endPos = new Position(
            rank + Board.FORWARD_DIR[this.colour.value],
            file - 1
        );

        move = new Move(startPos, this, endPos);

        if(Position.isValid(endPos) &&
            board.getPiece(endPos).colour == this.colour.getOther() &&
            !move.checksOwnKing(board)
        ) {
            legalMoves.add(move);
        }

        // Right attacking move
        endPos = new Position(
            rank + Board.FORWARD_DIR[this.colour.value],
            file + 1
        );

        move = new Move(startPos, this, endPos);

        if(Position.isValid(endPos) &&
            board.getPiece(endPos).colour == this.colour.getOther() &&
            !move.checksOwnKing(board)
        ) {
            legalMoves.add(move);
        }

        // Check for promotions
        if(endPos.rank == Board.MIN_RANK || endPos.rank == Board.MAX_RANK) {
            int originalSize = legalMoves.size();

            for(int i = 0; i < originalSize; i++) {
                move = legalMoves.pop();

                if(this.colour == Colour.WHITE) {
                    legalMoves.add(new Move(move.startPos, Piece.WHITE_BISHOP, move.endPos));
                    legalMoves.add(new Move(move.startPos, Piece.WHITE_ROOK, move.endPos));
                    legalMoves.add(new Move(move.startPos, Piece.WHITE_KNIGHT, move.endPos));
                    legalMoves.add(new Move(move.startPos, Piece.WHITE_QUEEN, move.endPos));
                }
                else {
                    legalMoves.add(new Move(move.startPos, Piece.BLACK_BISHOP, move.endPos));
                    legalMoves.add(new Move(move.startPos, Piece.BLACK_ROOK, move.endPos));
                    legalMoves.add(new Move(move.startPos, Piece.BLACK_KNIGHT, move.endPos));
                    legalMoves.add(new Move(move.startPos, Piece.BLACK_QUEEN, move.endPos));
                }
            }
        }

        return legalMoves;
    }
}
