package constellations.server

object Main extends App {

  println("hello constellation")

  // TODO : typesafe config
  // periodically listing room

  type GameStyle = String
  type Nick = String
  type Slot = Int
  type MapID = Int
  type HatID = Int
  type TauntID = String

  /**
    * Multiple players on same terminal : 1@nick, 2@nick, ...
    * Multiple terminal with same nick : nick-1, nick-2, ...
    * @param nick player name
    */
  final case class ConnectionRequest(nick: Nick)

  /**
    * On errors : nick empty if terminal does not have the newest version
    * @param finalNick player name validated by the server
    */
  final case class ConnectionRequestRes(finalNick: Nick)

  /**
    * Either joins an already existing match or creates a new one that will be launched in 30s.
    * @param gameStyle game style (if empty, joins a random match)
    * @param localPlayerCount number of local player
    * @param totalPlayerCount maximum number of player
    * @param desiredPlayers other players nick (reserve slots for given nick)
    * @param preferredMapID map whenever a match is created
    */
  final case class MatchRequest(gameStyle: Option[GameStyle], localPlayerCount: Int, totalPlayerCount: Int, desiredPlayers: List[Nick], preferredMapID: Option[MapID])

  /**
    * Fast answer to match request.
    * @param finalGameStyle selected game style
    */
  final case class MatchRequestRes(finalGameStyle: GameStyle, mapID: MapID)

  /**
    * Joins the lobby.
    * @param playerSlot player position
    * @param playerNick player name
    */
  final case class NewPlayerBrd(playerSlot: Slot, playerNick: String)

  /**
    * Left the lobby.
    */
  case object LeaveNotification

  /**
    * Leaves the lobby.
    * @param playerSlot player position
    */
  final case class PlayerLeaveBrd(playerSlot: Slot)

  /**
    * Changed player hat.
    * @param playerSlot player position
    * @param hatID new hat ID
    */
  final case class HatChange(playerSlot: Slot, hatID: HatID)

  /**
    * Changes player hat.
    * @param playerSlot player position
    * @param hatID new hat ID
    */
  final case class HatChangeBrd(playerSlot: Slot, hatID: HatID)

  /**
    * Changed player taunt.
    * @param playerSlot player position
    * @param tauntID new taunt ID
    */
  final case class RunTaunt(playerSlot: Slot, tauntID: TauntID)

  /**
    * Changes player taunt.
    * @param playerSlot player position
    * @param tauntID new taunt ID
    */
  final case class RunTauntBrd(playerSlot: Slot, tauntID: TauntID)

  /**
    * Changed player status.
    * @param playerSlot player position
    * @param ready new player status
    */
  final case class Status(playerSlot: Slot, ready: Boolean)

  /**
    * Changes player status.
    * @param playerSlot player position
    * @param ready new player status
    */
  final case class StatusBrd(playerSlot: Slot, ready: Boolean)

  /**
    * Count down to start from the last 10 seconds.
    * @param secToStart seconds to start
    */
  final case class CountDownBrd(secToStart: Int)

  /**
    * Match cancelled by an error or everything left.
    * @param cause cancel cause
    */
  final case class MatchCancelledBrd(cause: String)

  /**
    * Select the master which starts.
    * @param masterSlot player position
    */
  final case class MatchStartBrd(masterSlot: Slot)

  /**
    * Match ends.
    */
  case object MatchEnd

}
