#pragma once
#include "../math/math.hpp"


class cmove_data
{
public:
	bool			m_bFirstRunOfFunctions : 1;
	bool			m_bGameCodeMovedPlayer : 1;

	unsigned long	m_nPlayerHandle;	// edict index on server, client entity handle on client

	int				m_nImpulseCommand;	// Impulse command issued.
	vec3_t			m_vecViewAngles;	// Command view angles (local space)
	vec3_t			m_vecAbsViewAngles;	// Command view angles (world space)
	int				m_nButtons;			// Attack buttons.
	int				m_nOldButtons;		// From host_client->oldbuttons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;

	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;

	// Variables from the player edict (sv_player) or entvars on the client.
	// These are copied in here before calling and copied out after calling.
	vec3_t			m_vecVelocity;		// edict::velocity		// Current movement direction.
	vec3_t			m_vecAngles;		// edict::angles
	vec3_t			m_vecOldAngles;

	// Output only
	float			m_outStepHeight;	// how much you climbed this move
	vec3_t			m_outWishVel;		// This is where you tried 
	vec3_t			m_outJumpVel;		// This is your jump velocity

	// Movement constraints	(radius 0 means no constraint)
	vec3_t			m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;

	void			SetAbsOrigin(const vec3_t& vec);
	const vec3_t& GetAbsOrigin() const;

private:
	vec3_t			m_vecAbsOrigin;		// edict::origin
};

class i_move_helper {
public:

	void set_host(entity_t* host) {
		using original_fn = void(__thiscall*)(i_move_helper*, entity_t*);
		return (*(original_fn**)this)[1](this, host);
	}
};

class i_game_movement {
public:
	virtual			~i_game_movement(void) {}

	// Process the current movement command
	virtual void	ProcessMovement(player_t* pPlayer, cmove_data* pMove) = 0;
	virtual void	StartTrackPredictionErrors(player_t* pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(player_t* pPlayer) = 0;
	virtual void	DiffPrint(const char* fmt, ...) = 0;

	// Allows other parts of the engine to find out the normal and ducked player bbox sizes
	virtual vec3_t	GetPlayerMins(bool ducked) const = 0;
	virtual vec3_t	GetPlayerMaxs(bool ducked) const = 0;
	virtual vec3_t  GetPlayerViewOffset(bool ducked) const = 0;
};

class i_prediction
{
public:

	virtual			~i_prediction(void) {};

	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;

	// Run prediction
	virtual void	Update
	(
		int startframe,				// World update ( un-modded ) most recently received
		bool validframe,			// Is frame data valid
		int incoming_acknowledged,	// Last command acknowledged to have been run by server (un-modded)
		int outgoing_command		// Last command (most recent) sent to server (un-modded)
	) = 0;

	// We are about to get a network update from the server.  We know the update #, so we can pull any
	//  data purely predicted on the client side and transfer it to the new from data state.
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;

	virtual void	OnReceivedUncompressedPacket(void) = 0;

	// The engine needs to be able to access a few predicted values
	virtual void	GetViewOrigin(vec3_t& org) = 0;
	virtual void	SetViewOrigin(vec3_t& org) = 0;
	virtual void	GetViewAngles(vec3_t& ang) = 0;
	virtual void	SetViewAngles(vec3_t& ang) = 0;
	virtual void	GetLocalViewAngles(vec3_t& ang) = 0;
	virtual void	SetLocalViewAngles(vec3_t& ang) = 0;
};


extern i_prediction* prediction;