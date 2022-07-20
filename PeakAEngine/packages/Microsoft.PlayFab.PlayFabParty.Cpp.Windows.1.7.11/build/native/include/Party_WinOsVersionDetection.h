#pragma once

#ifdef __cplusplus
// Suppress VC++ Warning C26812: Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning(push)
#pragma warning(disable : 26812)
extern "C"
{
#endif

inline
PartyBool
PartyIsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
{
    OSVERSIONINFOEXA osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
    DWORDLONG dwlConditionMask = 0;
    dwlConditionMask = VerSetConditionMask(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
    dwlConditionMask = VerSetConditionMask(dwlConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL),
    dwlConditionMask = VerSetConditionMask(dwlConditionMask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

    osvi.dwMajorVersion = wMajorVersion;
    osvi.dwMinorVersion = wMinorVersion;
    osvi.wServicePackMajor = wServicePackMajor;

    return VerifyVersionInfoA(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
}

inline
PartyBool
PartyIsOsVersionWindows7()
{
    // Windows 8 and up is considered not Windows7.
    return !PartyIsWindowsVersionOrGreater(6, 2, 0);
}

// BEGIN GENERATED SECTION (declarations): DO NOT EDIT

typedef
PartyError
(PARTY_API* PartyLocalUserGetEntityId_FUNC)(
    PARTY_LOCAL_USER_HANDLE localUser,
    _Outptr_ PartyString* entityId
    );

typedef
PartyError
(PARTY_API* PartyLocalUserUpdateEntityToken_FUNC)(
    PARTY_LOCAL_USER_HANDLE localUser,
    PartyString titlePlayerEntityToken
    );

typedef
PartyError
(PARTY_API* PartyLocalUserGetCustomContext_FUNC)(
    PARTY_LOCAL_USER_HANDLE localUser,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyLocalUserSetCustomContext_FUNC)(
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetLocalUser_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_result_maybenull_ PARTY_LOCAL_USER_HANDLE* localUser
    );

typedef
PartyError
(PARTY_API* PartyEndpointSendMessage_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints,
    PARTY_SEND_MESSAGE_OPTIONS options,
    _In_opt_ const PARTY_SEND_MESSAGE_QUEUING_CONFIGURATION* queuingConfiguration,
    uint32_t dataBufferCount,
    _In_reads_(dataBufferCount) const PARTY_DATA_BUFFER* dataBuffers,
    _In_opt_ void* messageIdentifier
    );

typedef
PartyError
(PARTY_API* PartyEndpointCancelMessages_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints,
    PARTY_CANCEL_MESSAGES_FILTER_EXPRESSION filterExpression,
    uint32_t messageIdentityFilterMask,
    uint32_t filteredMessageIdentitiesToMatch,
    _Out_opt_ uint32_t* canceledMessagesCount
    );

typedef
PartyError
(PARTY_API* PartyEndpointFlushMessages_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetEndpointStatistics_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints,
    uint32_t statisticCount,
    _In_reads_(statisticCount) const PARTY_ENDPOINT_STATISTIC* statisticTypes,
    _Out_writes_all_(statisticCount) uint64_t* statisticValues
    );

typedef
PartyError
(PARTY_API* PartyEndpointIsLocal_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Out_ PartyBool* isLocal
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetEntityId_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_result_maybenull_ PartyString* entityId
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetNetwork_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_ PARTY_NETWORK_HANDLE* network
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetDevice_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_ PARTY_DEVICE_HANDLE* device
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetUniqueIdentifier_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Out_ uint16_t* uniqueIdentifier
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetSharedProperty_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetSharedPropertyKeys_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    );

typedef
PartyError
(PARTY_API* PartyEndpointSetSharedProperties_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    );

typedef
PartyError
(PARTY_API* PartyEndpointGetCustomContext_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyEndpointSetCustomContext_FUNC)(
    PARTY_ENDPOINT_HANDLE endpoint,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyDeviceCreateChatControl_FUNC)(
    PARTY_DEVICE_HANDLE device,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ PartyString languageCode,
    _In_opt_ void* asyncIdentifier,
    _Outptr_opt_ PARTY_CHAT_CONTROL_HANDLE* chatControl
    );

typedef
PartyError
(PARTY_API* PartyDeviceDestroyChatControl_FUNC)(
    PARTY_DEVICE_HANDLE device,
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyDeviceIsLocal_FUNC)(
    PARTY_DEVICE_HANDLE device,
    _Out_ PartyBool* isLocal
    );

typedef
PartyError
(PARTY_API* PartyDeviceGetChatControls_FUNC)(
    PARTY_DEVICE_HANDLE device,
    _Out_ uint32_t* chatControlCount,
    _Outptr_result_buffer_(*chatControlCount) const PARTY_CHAT_CONTROL_HANDLE** chatControls
    );

typedef
PartyError
(PARTY_API* PartyDeviceGetSharedProperty_FUNC)(
    PARTY_DEVICE_HANDLE device,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    );

typedef
PartyError
(PARTY_API* PartyDeviceGetSharedPropertyKeys_FUNC)(
    PARTY_DEVICE_HANDLE device,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    );

typedef
PartyError
(PARTY_API* PartyDeviceSetSharedProperties_FUNC)(
    PARTY_DEVICE_HANDLE device,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    );

typedef
PartyError
(PARTY_API* PartyDeviceGetCustomContext_FUNC)(
     PARTY_DEVICE_HANDLE device,
     _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyDeviceSetCustomContext_FUNC)(
    PARTY_DEVICE_HANDLE device,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyInvitationGetCreatorEntityId_FUNC)(
    PARTY_INVITATION_HANDLE invitation,
    _Outptr_result_maybenull_ PartyString * entityId
    );

typedef
PartyError
(PARTY_API* PartyInvitationGetInvitationConfiguration_FUNC)(
    PARTY_INVITATION_HANDLE invitation,
    _Outptr_ const PARTY_INVITATION_CONFIGURATION ** configuration
    );

typedef
PartyError
(PARTY_API* PartyInvitationGetCustomContext_FUNC)(
    PARTY_INVITATION_HANDLE invitation,
    _Outptr_result_maybenull_ void ** customContext
    );

typedef
PartyError
(PARTY_API* PartyInvitationSetCustomContext_FUNC)(
    PARTY_INVITATION_HANDLE invitation,
    _In_opt_ void * customContext
    );

typedef
PartyError
(PARTY_API* PartyNetworkAuthenticateLocalUser_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    PartyString invitationIdentifier,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkRemoveLocalUser_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkCreateInvitation_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ const PARTY_INVITATION_CONFIGURATION* invitationConfiguration,
    void* asyncIdentifier,
    _Outptr_opt_ PARTY_INVITATION_HANDLE* invitation
    );

typedef
PartyError
(PARTY_API* PartyNetworkRevokeInvitation_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    PARTY_INVITATION_HANDLE invitation,
    void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetInvitations_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* invitationCount,
    _Outptr_result_buffer_(*invitationCount) const PARTY_INVITATION_HANDLE** invitations
    );

typedef
PartyError
(PARTY_API* PartyNetworkCreateEndpoint_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _In_opt_ PARTY_LOCAL_USER_HANDLE localUser,
    uint32_t sharedPropertyCount,
    _In_reads_opt_(sharedPropertyCount) const PartyString* keys,
    _In_reads_opt_(sharedPropertyCount) const PARTY_DATA_BUFFER* values,
    _In_opt_ void* asyncIdentifier,
    _Outptr_opt_ PARTY_ENDPOINT_HANDLE* endpoint
    );

typedef
PartyError
(PARTY_API* PartyNetworkDestroyEndpoint_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_ENDPOINT_HANDLE localEndpoint,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkLeaveNetwork_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetEndpoints_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* endpointCount,
    _Outptr_result_buffer_(*endpointCount) const PARTY_ENDPOINT_HANDLE** endpoints
    );

typedef
PartyError
(PARTY_API* PartyNetworkFindEndpointByUniqueIdentifier_FUNC)(
    PARTY_NETWORK_HANDLE network,
    uint16_t uniqueIdentifier,
    _Outptr_ PARTY_ENDPOINT_HANDLE* endpoint
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetDevices_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* deviceCount,
    _Outptr_result_buffer_(*deviceCount) const PARTY_DEVICE_HANDLE** devices
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetLocalUsers_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* userCount,
    _Outptr_result_buffer_(*userCount) const PARTY_LOCAL_USER_HANDLE** users
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetNetworkDescriptor_FUNC)(
     PARTY_NETWORK_HANDLE network,
     _Out_ PARTY_NETWORK_DESCRIPTOR* networkDescriptor
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetNetworkConfiguration_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Outptr_ const PARTY_NETWORK_CONFIGURATION** networkConfiguration
    );

typedef
PartyError
(PARTY_API* PartyNetworkKickDevice_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_DEVICE_HANDLE targetDevice,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkKickUser_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PartyString targetEntityId,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetSharedProperty_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetSharedPropertyKeys_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    );

typedef
PartyError
(PARTY_API* PartyNetworkSetSharedProperties_FUNC)(
    PARTY_NETWORK_HANDLE network,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    );

typedef
PartyError
(PARTY_API* PartyNetworkConnectChatControl_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkDisconnectChatControl_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetChatControls_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* chatControlCount,
    _Outptr_result_buffer_(*chatControlCount) const PARTY_CHAT_CONTROL_HANDLE** chatControls
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetNetworkStatistics_FUNC)(
    PARTY_NETWORK_HANDLE network,
    uint32_t statisticCount,
    _In_reads_(statisticCount) const PARTY_NETWORK_STATISTIC* statisticTypes,
    _Out_writes_all_(statisticCount) uint64_t* statisticValues
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetCustomContext_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyNetworkSetCustomContext_FUNC)(
    PARTY_NETWORK_HANDLE network,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyNetworkGetDeviceConnectionType_FUNC)(
    PARTY_NETWORK_HANDLE network,
    PARTY_DEVICE_HANDLE targetDevice,
    _Out_ PARTY_DEVICE_CONNECTION_TYPE* deviceConnectionType
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetLocalUser_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_LOCAL_USER_HANDLE* localUser
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetPermissions_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    PARTY_CHAT_PERMISSION_OPTIONS chatPermissionOptions
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetPermissions_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PARTY_CHAT_PERMISSION_OPTIONS* chatPermissionOptions
    );

typedef
PartyError
(PARTY_API* PartyChatControlSendText_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    uint32_t targetChatControlCount,
    _In_reads_(targetChatControlCount) const PARTY_CHAT_CONTROL_HANDLE* targetChatControls,
    PartyString chatText,
    uint32_t dataBufferCount,
    _In_reads_(dataBufferCount) const PARTY_DATA_BUFFER* dataBuffers
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetAudioInput_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_AUDIO_DEVICE_SELECTION_TYPE audioDeviceSelectionType,
    _In_opt_ PartyString audioDeviceSelectionContext,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioInput_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_AUDIO_DEVICE_SELECTION_TYPE* audioDeviceSelectionType,
    _Outptr_ PartyString* audioDeviceSelectionContext,
    _Outptr_ PartyString* deviceId
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetAudioOutput_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_AUDIO_DEVICE_SELECTION_TYPE audioDeviceSelectionType,
    _In_opt_ PartyString audioDeviceSelectionContext,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioOutput_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_AUDIO_DEVICE_SELECTION_TYPE* audioDeviceSelectionType,
    _Outptr_ PartyString* audioDeviceSelectionContext,
    _Outptr_ PartyString* deviceId
    );

typedef
PartyError
(PARTY_API* PartyChatControlPopulateAvailableTextToSpeechProfiles_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAvailableTextToSpeechProfiles_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* profileCount,
    _Outptr_result_buffer_(*profileCount) const PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE** profiles
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetTextToSpeechProfile_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_SYNTHESIZE_TEXT_TO_SPEECH_TYPE type,
    _In_opt_ PartyString profileIdentifier,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetTextToSpeechProfile_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_SYNTHESIZE_TEXT_TO_SPEECH_TYPE type,
    _Outptr_result_maybenull_ PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE* profile
    );

typedef
PartyError
(PARTY_API* PartyChatControlSynthesizeTextToSpeech_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_SYNTHESIZE_TEXT_TO_SPEECH_TYPE type,
    PartyString textToSynthesize,
    _In_opt_ void * asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetLanguage_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PartyString languageCode,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetLanguage_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PartyString* languageCode
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetTranscriptionOptions_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_VOICE_CHAT_TRANSCRIPTION_OPTIONS options,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetTranscriptionOptions_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_VOICE_CHAT_TRANSCRIPTION_OPTIONS* options
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetTextChatOptions_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_TEXT_CHAT_OPTIONS options,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetTextChatOptions_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_TEXT_CHAT_OPTIONS* options
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetAudioRenderVolume_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    float volume
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioRenderVolume_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ float* volume
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetAudioInputMuted_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PartyBool muted
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioInputMuted_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PartyBool* muted
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetIncomingAudioMuted_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    PartyBool muted
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetIncomingAudioMuted_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PartyBool* muted
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetIncomingTextMuted_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    PartyBool muted
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetIncomingTextMuted_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PartyBool* muted
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetLocalChatIndicator_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_LOCAL_CHAT_CONTROL_CHAT_INDICATOR* chatIndicator
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetChatIndicator_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PARTY_CHAT_CONTROL_CHAT_INDICATOR* chatIndicator
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetAudioEncoderBitrate_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    uint32_t bitrate,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioEncoderBitrate_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* bitrate
    );

typedef
PartyError
(PARTY_API* PartyChatControlIsLocal_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PartyBool* isLocal
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetDevice_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_DEVICE_HANDLE* device
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetEntityId_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PartyString* entityId
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetSharedProperty_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetSharedPropertyKeys_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetSharedProperties_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetNetworks_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* networkCount,
    _Outptr_result_buffer_(*networkCount) const PARTY_NETWORK_HANDLE** networks
    );

typedef
PartyError
(PARTY_API* PartyChatControlSetCustomContext_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetCustomContext_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyChatControlConfigureAudioManipulationVoiceStream_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_CONFIGURATION* configuration,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioManipulationVoiceStream_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE* stream
    );

typedef
PartyError
(PARTY_API* PartyChatControlConfigureAudioManipulationCaptureStream_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_CONFIGURATION* configuration,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioManipulationCaptureStream_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE* stream
    );

typedef
PartyError
(PARTY_API* PartyChatControlConfigureAudioManipulationRenderStream_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_CONFIGURATION* configuration,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyChatControlGetAudioManipulationRenderStream_FUNC)(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE* stream
    );

typedef
PartyError
(PARTY_API* PartyTextToSpeechProfileGetIdentifier_FUNC)(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_ PartyString* identifier
    );

typedef
PartyError
(PARTY_API* PartyTextToSpeechProfileGetName_FUNC)(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_ PartyString* name
    );

typedef
PartyError
(PARTY_API* PartyTextToSpeechProfileGetLanguageCode_FUNC)(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_ PartyString* languageCode
    );

typedef
PartyError
(PARTY_API* PartyTextToSpeechProfileGetGender_FUNC)(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Out_ PARTY_GENDER* gender
    );

typedef
PartyError
(PARTY_API* PartyTextToSpeechProfileGetCustomContext_FUNC)(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyTextToSpeechProfileSetCustomContext_FUNC)(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamGetConfiguration_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_CONFIGURATION * configuration
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamGetFormat_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_FORMAT * format
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamGetAvailableBufferCount_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ uint32_t* count
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamGetNextBuffer_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ PARTY_MUTABLE_DATA_BUFFER* buffer
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamReturnBuffer_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Post_invalid_ void * buffer
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamGetCustomContext_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSourceStreamSetCustomContext_FUNC)(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSinkStreamGetConfiguration_FUNC)(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_CONFIGURATION * configuration
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSinkStreamGetFormat_FUNC)(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_FORMAT* format
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSinkStreamSubmitBuffer_FUNC)(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    const PARTY_DATA_BUFFER* buffer
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSinkStreamGetCustomContext_FUNC)(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _Outptr_result_maybenull_ void** customContext
    );

typedef
PartyError
(PARTY_API* PartyAudioManipulationSinkStreamSetCustomContext_FUNC)(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _In_opt_ void* customContext
    );

typedef
PartyError
(PARTY_API* PartySetOption_FUNC)(
    _In_opt_ void* object,
    PARTY_OPTION option,
    _In_opt_ const void* value
    );

typedef
PartyError
(PARTY_API* PartyGetOption_FUNC)(
    _In_opt_ const void* object,
    PARTY_OPTION option,
    _Out_ void* value
    );

typedef
PartyError
(PARTY_API* PartyGetErrorMessage_FUNC)(
    PartyError error,
    _Outptr_ PartyString* errorMessage
    );

typedef
PartyError
(PARTY_API* PartySerializeNetworkDescriptor_FUNC)(
    const PARTY_NETWORK_DESCRIPTOR* networkDescriptor,
    _Out_writes_z_(PARTY_MAX_SERIALIZED_NETWORK_DESCRIPTOR_STRING_LENGTH + 1) char* serializedNetworkDescriptorString
    );

typedef
PartyError
(PARTY_API* PartyDeserializeNetworkDescriptor_FUNC)(
    PartyString serializedNetworkDescriptorString,
    _Out_ PARTY_NETWORK_DESCRIPTOR* networkDescriptor
    );

typedef
PartyError
(PARTY_API* PartySetMemoryCallbacks_FUNC)(
    _In_ PARTY_MEM_ALLOC_FUNC allocateMemoryCallback,
    _In_ PARTY_MEM_FREE_FUNC freeMemoryCallback
    );

typedef
PartyError
(PARTY_API* PartyGetMemoryCallbacks_FUNC)(
    _Out_ PARTY_MEM_ALLOC_FUNC* allocateMemoryCallback,
    _Out_ PARTY_MEM_FREE_FUNC* freeMemoryCallback
    );

typedef
PartyError
(PARTY_API* PartySetProfilingCallbacksForMethodEntryExit_FUNC)(
    _In_opt_ PARTY_PROFILING_METHOD_ENTRANCE_FUNC profilingMethodEntranceCallback,
    _In_opt_ PARTY_PROFILING_METHOD_EXIT_FUNC profilingMethodExitCallback
    );

typedef
PartyError
(PARTY_API* PartyGetProfilingCallbacksForMethodEntryExit_FUNC)(
    _Outptr_result_maybenull_ PARTY_PROFILING_METHOD_ENTRANCE_FUNC* profilingMethodEntranceCallback,
    _Outptr_result_maybenull_ PARTY_PROFILING_METHOD_EXIT_FUNC* profilingMethodExitCallback
    );

typedef
PartyError
(PARTY_API* PartySetThreadAffinityMask_FUNC)(
    PARTY_THREAD_ID threadId,
    uint64_t threadAffinityMask
    );

typedef
PartyError
(PARTY_API* PartyGetThreadAffinityMask_FUNC)(
    PARTY_THREAD_ID threadId,
    _Out_ uint64_t* threadAffinityMask
    );

typedef
PartyError
(PARTY_API* PartySetWorkMode_FUNC)(
    PARTY_THREAD_ID threadId,
    PARTY_WORK_MODE workMode
    );

typedef
PartyError
(PARTY_API* PartyGetWorkMode_FUNC)(
    PARTY_THREAD_ID threadId,
    _Out_ PARTY_WORK_MODE * workMode
    );

typedef
PartyError
(PARTY_API* PartyInitialize_FUNC)(
    PartyString titleId,
    _Outptr_ PARTY_HANDLE* handle
    );

typedef
PartyError
(PARTY_API* PartyCleanup_FUNC)(
    _Post_invalid_ PARTY_HANDLE handle
    );

typedef
PartyError
(PARTY_API* PartyStartProcessingStateChanges_FUNC)(
    PARTY_HANDLE handle,
    _Out_ uint32_t* stateChangeCount,
    _Outptr_result_buffer_(*stateChangeCount) const PARTY_STATE_CHANGE*const** stateChanges
    );

typedef
PartyError
(PARTY_API* PartyFinishProcessingStateChanges_FUNC)(
    PARTY_HANDLE handle,
    uint32_t stateChangeCount,
    _In_reads_(stateChangeCount) const PARTY_STATE_CHANGE*const* stateChanges
    );

typedef
PartyError
(PARTY_API* PartyDoWork_FUNC)(
    PARTY_HANDLE handle,
    PARTY_THREAD_ID threadId
    );

typedef
PartyError
(PARTY_API* PartyGetRegions_FUNC)(
    PARTY_HANDLE handle,
    _Out_ uint32_t* regionListCount,
    _Outptr_result_buffer_(*regionListCount) const PARTY_REGION** regionList
    );

typedef
PartyError
(PARTY_API* PartyCreateNewNetwork_FUNC)(
    PARTY_HANDLE handle,
    PARTY_LOCAL_USER_HANDLE localUser,
    const PARTY_NETWORK_CONFIGURATION* networkConfiguration,
    uint32_t regionCount,
    _In_reads_(regionCount) const PARTY_REGION* regions,
    _In_opt_ const PARTY_INVITATION_CONFIGURATION* initialInvitationConfiguration,
    _In_opt_ void * asyncIdentifier,
    _Out_opt_ PARTY_NETWORK_DESCRIPTOR* networkDescriptor,
    _Out_writes_opt_z_(PARTY_MAX_INVITATION_IDENTIFIER_STRING_LENGTH + 1) char * appliedInitialInvitationIdentifier
    );

typedef
PartyError
(PARTY_API* PartyConnectToNetwork_FUNC)(
    PARTY_HANDLE handle,
    const PARTY_NETWORK_DESCRIPTOR* networkDescriptor,
    _In_opt_ void* asyncIdentifier,
    _Outptr_opt_ PARTY_NETWORK_HANDLE* network
    );

typedef
PartyError
(PARTY_API* PartySynchronizeMessagesBetweenEndpoints_FUNC)(
    PARTY_HANDLE handle,
    uint32_t endpointCount,
    _In_reads_(endpointCount) const PARTY_ENDPOINT_HANDLE* endpoints,
    PARTY_SYNCHRONIZE_MESSAGES_BETWEEN_ENDPOINTS_OPTIONS options,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyGetLocalDevice_FUNC)(
    PARTY_HANDLE handle,
    _Outptr_ PARTY_DEVICE_HANDLE* localDevice
    );

typedef
PartyError
(PARTY_API* PartyCreateLocalUser_FUNC)(
    PARTY_HANDLE handle,
    PartyString entityId,
    PartyString titlePlayerEntityToken,
    _Outptr_ PARTY_LOCAL_USER_HANDLE* localUser
    );

typedef
PartyError
(PARTY_API* PartyDestroyLocalUser_FUNC)(
    PARTY_HANDLE handle,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ void* asyncIdentifier
    );

typedef
PartyError
(PARTY_API* PartyGetLocalUsers_FUNC)(
    PARTY_HANDLE handle,
    _Out_ uint32_t* userCount,
    _Outptr_result_buffer_(*userCount) const PARTY_LOCAL_USER_HANDLE** users
    );

typedef
PartyError
(PARTY_API* PartyGetNetworks_FUNC)(
    PARTY_HANDLE handle,
    _Out_ uint32_t* networkCount,
    _Outptr_result_buffer_(*networkCount) const PARTY_NETWORK_HANDLE** networks
    );

typedef
PartyError
(PARTY_API* PartyGetChatControls_FUNC)(
    PARTY_HANDLE handle,
    _Out_ uint32_t* chatControlCount,
    _Outptr_result_buffer_(*chatControlCount) const PARTY_CHAT_CONTROL_HANDLE** chatControls
    );

typedef struct {
    PartyLocalUserGetEntityId_FUNC PartyLocalUserGetEntityId;
    PartyLocalUserUpdateEntityToken_FUNC PartyLocalUserUpdateEntityToken;
    PartyLocalUserGetCustomContext_FUNC PartyLocalUserGetCustomContext;
    PartyLocalUserSetCustomContext_FUNC PartyLocalUserSetCustomContext;
    PartyEndpointGetLocalUser_FUNC PartyEndpointGetLocalUser;
    PartyEndpointSendMessage_FUNC PartyEndpointSendMessage;
    PartyEndpointCancelMessages_FUNC PartyEndpointCancelMessages;
    PartyEndpointFlushMessages_FUNC PartyEndpointFlushMessages;
    PartyEndpointGetEndpointStatistics_FUNC PartyEndpointGetEndpointStatistics;
    PartyEndpointIsLocal_FUNC PartyEndpointIsLocal;
    PartyEndpointGetEntityId_FUNC PartyEndpointGetEntityId;
    PartyEndpointGetNetwork_FUNC PartyEndpointGetNetwork;
    PartyEndpointGetDevice_FUNC PartyEndpointGetDevice;
    PartyEndpointGetUniqueIdentifier_FUNC PartyEndpointGetUniqueIdentifier;
    PartyEndpointGetSharedProperty_FUNC PartyEndpointGetSharedProperty;
    PartyEndpointGetSharedPropertyKeys_FUNC PartyEndpointGetSharedPropertyKeys;
    PartyEndpointSetSharedProperties_FUNC PartyEndpointSetSharedProperties;
    PartyEndpointGetCustomContext_FUNC PartyEndpointGetCustomContext;
    PartyEndpointSetCustomContext_FUNC PartyEndpointSetCustomContext;
    PartyDeviceCreateChatControl_FUNC PartyDeviceCreateChatControl;
    PartyDeviceDestroyChatControl_FUNC PartyDeviceDestroyChatControl;
    PartyDeviceIsLocal_FUNC PartyDeviceIsLocal;
    PartyDeviceGetChatControls_FUNC PartyDeviceGetChatControls;
    PartyDeviceGetSharedProperty_FUNC PartyDeviceGetSharedProperty;
    PartyDeviceGetSharedPropertyKeys_FUNC PartyDeviceGetSharedPropertyKeys;
    PartyDeviceSetSharedProperties_FUNC PartyDeviceSetSharedProperties;
    PartyDeviceGetCustomContext_FUNC PartyDeviceGetCustomContext;
    PartyDeviceSetCustomContext_FUNC PartyDeviceSetCustomContext;
    PartyInvitationGetCreatorEntityId_FUNC PartyInvitationGetCreatorEntityId;
    PartyInvitationGetInvitationConfiguration_FUNC PartyInvitationGetInvitationConfiguration;
    PartyInvitationGetCustomContext_FUNC PartyInvitationGetCustomContext;
    PartyInvitationSetCustomContext_FUNC PartyInvitationSetCustomContext;
    PartyNetworkAuthenticateLocalUser_FUNC PartyNetworkAuthenticateLocalUser;
    PartyNetworkRemoveLocalUser_FUNC PartyNetworkRemoveLocalUser;
    PartyNetworkCreateInvitation_FUNC PartyNetworkCreateInvitation;
    PartyNetworkRevokeInvitation_FUNC PartyNetworkRevokeInvitation;
    PartyNetworkGetInvitations_FUNC PartyNetworkGetInvitations;
    PartyNetworkCreateEndpoint_FUNC PartyNetworkCreateEndpoint;
    PartyNetworkDestroyEndpoint_FUNC PartyNetworkDestroyEndpoint;
    PartyNetworkLeaveNetwork_FUNC PartyNetworkLeaveNetwork;
    PartyNetworkGetEndpoints_FUNC PartyNetworkGetEndpoints;
    PartyNetworkFindEndpointByUniqueIdentifier_FUNC PartyNetworkFindEndpointByUniqueIdentifier;
    PartyNetworkGetDevices_FUNC PartyNetworkGetDevices;
    PartyNetworkGetLocalUsers_FUNC PartyNetworkGetLocalUsers;
    PartyNetworkGetNetworkDescriptor_FUNC PartyNetworkGetNetworkDescriptor;
    PartyNetworkGetNetworkConfiguration_FUNC PartyNetworkGetNetworkConfiguration;
    PartyNetworkKickDevice_FUNC PartyNetworkKickDevice;
    PartyNetworkKickUser_FUNC PartyNetworkKickUser;
    PartyNetworkGetSharedProperty_FUNC PartyNetworkGetSharedProperty;
    PartyNetworkGetSharedPropertyKeys_FUNC PartyNetworkGetSharedPropertyKeys;
    PartyNetworkSetSharedProperties_FUNC PartyNetworkSetSharedProperties;
    PartyNetworkConnectChatControl_FUNC PartyNetworkConnectChatControl;
    PartyNetworkDisconnectChatControl_FUNC PartyNetworkDisconnectChatControl;
    PartyNetworkGetChatControls_FUNC PartyNetworkGetChatControls;
    PartyNetworkGetNetworkStatistics_FUNC PartyNetworkGetNetworkStatistics;
    PartyNetworkGetCustomContext_FUNC PartyNetworkGetCustomContext;
    PartyNetworkSetCustomContext_FUNC PartyNetworkSetCustomContext;
    PartyNetworkGetDeviceConnectionType_FUNC PartyNetworkGetDeviceConnectionType;
    PartyChatControlGetLocalUser_FUNC PartyChatControlGetLocalUser;
    PartyChatControlSetPermissions_FUNC PartyChatControlSetPermissions;
    PartyChatControlGetPermissions_FUNC PartyChatControlGetPermissions;
    PartyChatControlSendText_FUNC PartyChatControlSendText;
    PartyChatControlSetAudioInput_FUNC PartyChatControlSetAudioInput;
    PartyChatControlGetAudioInput_FUNC PartyChatControlGetAudioInput;
    PartyChatControlSetAudioOutput_FUNC PartyChatControlSetAudioOutput;
    PartyChatControlGetAudioOutput_FUNC PartyChatControlGetAudioOutput;
    PartyChatControlPopulateAvailableTextToSpeechProfiles_FUNC PartyChatControlPopulateAvailableTextToSpeechProfiles;
    PartyChatControlGetAvailableTextToSpeechProfiles_FUNC PartyChatControlGetAvailableTextToSpeechProfiles;
    PartyChatControlSetTextToSpeechProfile_FUNC PartyChatControlSetTextToSpeechProfile;
    PartyChatControlGetTextToSpeechProfile_FUNC PartyChatControlGetTextToSpeechProfile;
    PartyChatControlSynthesizeTextToSpeech_FUNC PartyChatControlSynthesizeTextToSpeech;
    PartyChatControlSetLanguage_FUNC PartyChatControlSetLanguage;
    PartyChatControlGetLanguage_FUNC PartyChatControlGetLanguage;
    PartyChatControlSetTranscriptionOptions_FUNC PartyChatControlSetTranscriptionOptions;
    PartyChatControlGetTranscriptionOptions_FUNC PartyChatControlGetTranscriptionOptions;
    PartyChatControlSetTextChatOptions_FUNC PartyChatControlSetTextChatOptions;
    PartyChatControlGetTextChatOptions_FUNC PartyChatControlGetTextChatOptions;
    PartyChatControlSetAudioRenderVolume_FUNC PartyChatControlSetAudioRenderVolume;
    PartyChatControlGetAudioRenderVolume_FUNC PartyChatControlGetAudioRenderVolume;
    PartyChatControlSetAudioInputMuted_FUNC PartyChatControlSetAudioInputMuted;
    PartyChatControlGetAudioInputMuted_FUNC PartyChatControlGetAudioInputMuted;
    PartyChatControlSetIncomingAudioMuted_FUNC PartyChatControlSetIncomingAudioMuted;
    PartyChatControlGetIncomingAudioMuted_FUNC PartyChatControlGetIncomingAudioMuted;
    PartyChatControlSetIncomingTextMuted_FUNC PartyChatControlSetIncomingTextMuted;
    PartyChatControlGetIncomingTextMuted_FUNC PartyChatControlGetIncomingTextMuted;
    PartyChatControlGetLocalChatIndicator_FUNC PartyChatControlGetLocalChatIndicator;
    PartyChatControlGetChatIndicator_FUNC PartyChatControlGetChatIndicator;
    PartyChatControlSetAudioEncoderBitrate_FUNC PartyChatControlSetAudioEncoderBitrate;
    PartyChatControlGetAudioEncoderBitrate_FUNC PartyChatControlGetAudioEncoderBitrate;
    PartyChatControlIsLocal_FUNC PartyChatControlIsLocal;
    PartyChatControlGetDevice_FUNC PartyChatControlGetDevice;
    PartyChatControlGetEntityId_FUNC PartyChatControlGetEntityId;
    PartyChatControlGetSharedProperty_FUNC PartyChatControlGetSharedProperty;
    PartyChatControlGetSharedPropertyKeys_FUNC PartyChatControlGetSharedPropertyKeys;
    PartyChatControlSetSharedProperties_FUNC PartyChatControlSetSharedProperties;
    PartyChatControlGetNetworks_FUNC PartyChatControlGetNetworks;
    PartyChatControlSetCustomContext_FUNC PartyChatControlSetCustomContext;
    PartyChatControlGetCustomContext_FUNC PartyChatControlGetCustomContext;
    PartyChatControlConfigureAudioManipulationVoiceStream_FUNC PartyChatControlConfigureAudioManipulationVoiceStream;
    PartyChatControlGetAudioManipulationVoiceStream_FUNC PartyChatControlGetAudioManipulationVoiceStream;
    PartyChatControlConfigureAudioManipulationCaptureStream_FUNC PartyChatControlConfigureAudioManipulationCaptureStream;
    PartyChatControlGetAudioManipulationCaptureStream_FUNC PartyChatControlGetAudioManipulationCaptureStream;
    PartyChatControlConfigureAudioManipulationRenderStream_FUNC PartyChatControlConfigureAudioManipulationRenderStream;
    PartyChatControlGetAudioManipulationRenderStream_FUNC PartyChatControlGetAudioManipulationRenderStream;
    PartyTextToSpeechProfileGetIdentifier_FUNC PartyTextToSpeechProfileGetIdentifier;
    PartyTextToSpeechProfileGetName_FUNC PartyTextToSpeechProfileGetName;
    PartyTextToSpeechProfileGetLanguageCode_FUNC PartyTextToSpeechProfileGetLanguageCode;
    PartyTextToSpeechProfileGetGender_FUNC PartyTextToSpeechProfileGetGender;
    PartyTextToSpeechProfileGetCustomContext_FUNC PartyTextToSpeechProfileGetCustomContext;
    PartyTextToSpeechProfileSetCustomContext_FUNC PartyTextToSpeechProfileSetCustomContext;
    PartyAudioManipulationSourceStreamGetConfiguration_FUNC PartyAudioManipulationSourceStreamGetConfiguration;
    PartyAudioManipulationSourceStreamGetFormat_FUNC PartyAudioManipulationSourceStreamGetFormat;
    PartyAudioManipulationSourceStreamGetAvailableBufferCount_FUNC PartyAudioManipulationSourceStreamGetAvailableBufferCount;
    PartyAudioManipulationSourceStreamGetNextBuffer_FUNC PartyAudioManipulationSourceStreamGetNextBuffer;
    PartyAudioManipulationSourceStreamReturnBuffer_FUNC PartyAudioManipulationSourceStreamReturnBuffer;
    PartyAudioManipulationSourceStreamGetCustomContext_FUNC PartyAudioManipulationSourceStreamGetCustomContext;
    PartyAudioManipulationSourceStreamSetCustomContext_FUNC PartyAudioManipulationSourceStreamSetCustomContext;
    PartyAudioManipulationSinkStreamGetConfiguration_FUNC PartyAudioManipulationSinkStreamGetConfiguration;
    PartyAudioManipulationSinkStreamGetFormat_FUNC PartyAudioManipulationSinkStreamGetFormat;
    PartyAudioManipulationSinkStreamSubmitBuffer_FUNC PartyAudioManipulationSinkStreamSubmitBuffer;
    PartyAudioManipulationSinkStreamGetCustomContext_FUNC PartyAudioManipulationSinkStreamGetCustomContext;
    PartyAudioManipulationSinkStreamSetCustomContext_FUNC PartyAudioManipulationSinkStreamSetCustomContext;
    PartySetOption_FUNC PartySetOption;
    PartyGetOption_FUNC PartyGetOption;
    PartyGetErrorMessage_FUNC PartyGetErrorMessage;
    PartySerializeNetworkDescriptor_FUNC PartySerializeNetworkDescriptor;
    PartyDeserializeNetworkDescriptor_FUNC PartyDeserializeNetworkDescriptor;
    PartySetMemoryCallbacks_FUNC PartySetMemoryCallbacks;
    PartyGetMemoryCallbacks_FUNC PartyGetMemoryCallbacks;
    PartySetProfilingCallbacksForMethodEntryExit_FUNC PartySetProfilingCallbacksForMethodEntryExit;
    PartyGetProfilingCallbacksForMethodEntryExit_FUNC PartyGetProfilingCallbacksForMethodEntryExit;
    PartySetThreadAffinityMask_FUNC PartySetThreadAffinityMask;
    PartyGetThreadAffinityMask_FUNC PartyGetThreadAffinityMask;
    PartySetWorkMode_FUNC PartySetWorkMode;
    PartyGetWorkMode_FUNC PartyGetWorkMode;
    PartyInitialize_FUNC PartyInitialize;
    PartyCleanup_FUNC PartyCleanup;
    PartyStartProcessingStateChanges_FUNC PartyStartProcessingStateChanges;
    PartyFinishProcessingStateChanges_FUNC PartyFinishProcessingStateChanges;
    PartyDoWork_FUNC PartyDoWork;
    PartyGetRegions_FUNC PartyGetRegions;
    PartyCreateNewNetwork_FUNC PartyCreateNewNetwork;
    PartyConnectToNetwork_FUNC PartyConnectToNetwork;
    PartySynchronizeMessagesBetweenEndpoints_FUNC PartySynchronizeMessagesBetweenEndpoints;
    PartyGetLocalDevice_FUNC PartyGetLocalDevice;
    PartyCreateLocalUser_FUNC PartyCreateLocalUser;
    PartyDestroyLocalUser_FUNC PartyDestroyLocalUser;
    PartyGetLocalUsers_FUNC PartyGetLocalUsers;
    PartyGetNetworks_FUNC PartyGetNetworks;
    PartyGetChatControls_FUNC PartyGetChatControls;
} PARTY_FUNCTION_TABLE;

#define PARTY_FUNCTION_COUNT 150

// END GENERATED SECTION

typedef union {
    void* FunctionArray[PARTY_FUNCTION_COUNT];
    PARTY_FUNCTION_TABLE FunctionTable;
} PARTY_FUNCTIONS;

#pragma push_macro("PARTY_C_ASSERT")
#pragma push_macro("PARTY_MEMBER_SIZEOF")
#undef PARTY_C_ASSERT
#undef PARTY_MEMBER_SIZEOF
#define PARTY_C_ASSERT(e) typedef char __PARTY_C_ASSERT__[(e)?1:-1]
#define PARTY_MEMBER_SIZEOF(structName, fieldName) sizeof(((structName *)0)->fieldName)

PARTY_C_ASSERT(PARTY_MEMBER_SIZEOF(PARTY_FUNCTIONS, FunctionArray[0]) == sizeof(PartyInitialize_FUNC));
PARTY_C_ASSERT(PARTY_MEMBER_SIZEOF(PARTY_FUNCTIONS, FunctionArray) == PARTY_MEMBER_SIZEOF(PARTY_FUNCTIONS, FunctionTable));

inline
PartyError
PartyLoadWindowsDllExports(
    HMODULE partyDll,
    _Out_ PARTY_FUNCTIONS* partyFunctions
    )
{
    static const PartyString s_partyFunctionNames[] =
    {
// BEGIN GENERATED SECTION (function_names): DO NOT EDIT
        "PartyLocalUserGetEntityId",
        "PartyLocalUserUpdateEntityToken",
        "PartyLocalUserGetCustomContext",
        "PartyLocalUserSetCustomContext",
        "PartyEndpointGetLocalUser",
        "PartyEndpointSendMessage",
        "PartyEndpointCancelMessages",
        "PartyEndpointFlushMessages",
        "PartyEndpointGetEndpointStatistics",
        "PartyEndpointIsLocal",
        "PartyEndpointGetEntityId",
        "PartyEndpointGetNetwork",
        "PartyEndpointGetDevice",
        "PartyEndpointGetUniqueIdentifier",
        "PartyEndpointGetSharedProperty",
        "PartyEndpointGetSharedPropertyKeys",
        "PartyEndpointSetSharedProperties",
        "PartyEndpointGetCustomContext",
        "PartyEndpointSetCustomContext",
        "PartyDeviceCreateChatControl",
        "PartyDeviceDestroyChatControl",
        "PartyDeviceIsLocal",
        "PartyDeviceGetChatControls",
        "PartyDeviceGetSharedProperty",
        "PartyDeviceGetSharedPropertyKeys",
        "PartyDeviceSetSharedProperties",
        "PartyDeviceGetCustomContext",
        "PartyDeviceSetCustomContext",
        "PartyInvitationGetCreatorEntityId",
        "PartyInvitationGetInvitationConfiguration",
        "PartyInvitationGetCustomContext",
        "PartyInvitationSetCustomContext",
        "PartyNetworkAuthenticateLocalUser",
        "PartyNetworkRemoveLocalUser",
        "PartyNetworkCreateInvitation",
        "PartyNetworkRevokeInvitation",
        "PartyNetworkGetInvitations",
        "PartyNetworkCreateEndpoint",
        "PartyNetworkDestroyEndpoint",
        "PartyNetworkLeaveNetwork",
        "PartyNetworkGetEndpoints",
        "PartyNetworkFindEndpointByUniqueIdentifier",
        "PartyNetworkGetDevices",
        "PartyNetworkGetLocalUsers",
        "PartyNetworkGetNetworkDescriptor",
        "PartyNetworkGetNetworkConfiguration",
        "PartyNetworkKickDevice",
        "PartyNetworkKickUser",
        "PartyNetworkGetSharedProperty",
        "PartyNetworkGetSharedPropertyKeys",
        "PartyNetworkSetSharedProperties",
        "PartyNetworkConnectChatControl",
        "PartyNetworkDisconnectChatControl",
        "PartyNetworkGetChatControls",
        "PartyNetworkGetNetworkStatistics",
        "PartyNetworkGetCustomContext",
        "PartyNetworkSetCustomContext",
        "PartyNetworkGetDeviceConnectionType",
        "PartyChatControlGetLocalUser",
        "PartyChatControlSetPermissions",
        "PartyChatControlGetPermissions",
        "PartyChatControlSendText",
        "PartyChatControlSetAudioInput",
        "PartyChatControlGetAudioInput",
        "PartyChatControlSetAudioOutput",
        "PartyChatControlGetAudioOutput",
        "PartyChatControlPopulateAvailableTextToSpeechProfiles",
        "PartyChatControlGetAvailableTextToSpeechProfiles",
        "PartyChatControlSetTextToSpeechProfile",
        "PartyChatControlGetTextToSpeechProfile",
        "PartyChatControlSynthesizeTextToSpeech",
        "PartyChatControlSetLanguage",
        "PartyChatControlGetLanguage",
        "PartyChatControlSetTranscriptionOptions",
        "PartyChatControlGetTranscriptionOptions",
        "PartyChatControlSetTextChatOptions",
        "PartyChatControlGetTextChatOptions",
        "PartyChatControlSetAudioRenderVolume",
        "PartyChatControlGetAudioRenderVolume",
        "PartyChatControlSetAudioInputMuted",
        "PartyChatControlGetAudioInputMuted",
        "PartyChatControlSetIncomingAudioMuted",
        "PartyChatControlGetIncomingAudioMuted",
        "PartyChatControlSetIncomingTextMuted",
        "PartyChatControlGetIncomingTextMuted",
        "PartyChatControlGetLocalChatIndicator",
        "PartyChatControlGetChatIndicator",
        "PartyChatControlSetAudioEncoderBitrate",
        "PartyChatControlGetAudioEncoderBitrate",
        "PartyChatControlIsLocal",
        "PartyChatControlGetDevice",
        "PartyChatControlGetEntityId",
        "PartyChatControlGetSharedProperty",
        "PartyChatControlGetSharedPropertyKeys",
        "PartyChatControlSetSharedProperties",
        "PartyChatControlGetNetworks",
        "PartyChatControlSetCustomContext",
        "PartyChatControlGetCustomContext",
        "PartyChatControlConfigureAudioManipulationVoiceStream",
        "PartyChatControlGetAudioManipulationVoiceStream",
        "PartyChatControlConfigureAudioManipulationCaptureStream",
        "PartyChatControlGetAudioManipulationCaptureStream",
        "PartyChatControlConfigureAudioManipulationRenderStream",
        "PartyChatControlGetAudioManipulationRenderStream",
        "PartyTextToSpeechProfileGetIdentifier",
        "PartyTextToSpeechProfileGetName",
        "PartyTextToSpeechProfileGetLanguageCode",
        "PartyTextToSpeechProfileGetGender",
        "PartyTextToSpeechProfileGetCustomContext",
        "PartyTextToSpeechProfileSetCustomContext",
        "PartyAudioManipulationSourceStreamGetConfiguration",
        "PartyAudioManipulationSourceStreamGetFormat",
        "PartyAudioManipulationSourceStreamGetAvailableBufferCount",
        "PartyAudioManipulationSourceStreamGetNextBuffer",
        "PartyAudioManipulationSourceStreamReturnBuffer",
        "PartyAudioManipulationSourceStreamGetCustomContext",
        "PartyAudioManipulationSourceStreamSetCustomContext",
        "PartyAudioManipulationSinkStreamGetConfiguration",
        "PartyAudioManipulationSinkStreamGetFormat",
        "PartyAudioManipulationSinkStreamSubmitBuffer",
        "PartyAudioManipulationSinkStreamGetCustomContext",
        "PartyAudioManipulationSinkStreamSetCustomContext",
        "PartySetOption",
        "PartyGetOption",
        "PartyGetErrorMessage",
        "PartySerializeNetworkDescriptor",
        "PartyDeserializeNetworkDescriptor",
        "PartySetMemoryCallbacks",
        "PartyGetMemoryCallbacks",
        "PartySetProfilingCallbacksForMethodEntryExit",
        "PartyGetProfilingCallbacksForMethodEntryExit",
        "PartySetThreadAffinityMask",
        "PartyGetThreadAffinityMask",
        "PartySetWorkMode",
        "PartyGetWorkMode",
        "PartyInitialize",
        "PartyCleanup",
        "PartyStartProcessingStateChanges",
        "PartyFinishProcessingStateChanges",
        "PartyDoWork",
        "PartyGetRegions",
        "PartyCreateNewNetwork",
        "PartyConnectToNetwork",
        "PartySynchronizeMessagesBetweenEndpoints",
        "PartyGetLocalDevice",
        "PartyCreateLocalUser",
        "PartyDestroyLocalUser",
        "PartyGetLocalUsers",
        "PartyGetNetworks",
        "PartyGetChatControls"
// END GENERATED SECTION
    };

    PARTY_C_ASSERT(ARRAYSIZE(s_partyFunctionNames) == PARTY_FUNCTION_COUNT);
    memset(partyFunctions, 0, sizeof(partyFunctions));

    for (unsigned int i = 0; i < ARRAYSIZE(s_partyFunctionNames); ++i)
    {
        partyFunctions->FunctionArray[i] = (void*)GetProcAddress(partyDll, s_partyFunctionNames[i]);
        if (partyFunctions->FunctionArray[i] == NULL)
        {
            return c_partyErrorFailedLoadingPartyModule;
        }
    }

    return c_partyErrorSuccess;
}

#pragma pop_macro("PARTY_MEMBER_SIZEOF")
#pragma pop_macro("PARTY_C_ASSERT")

inline
PartyError
PartyGetWindowsDllExports(
   _Outptr_ const PARTY_FUNCTIONS** partyFunctions
   )
{
    static PARTY_FUNCTIONS s_partyFunctions;

    if (s_partyFunctions.FunctionTable.PartyInitialize == NULL)
    {
        PartyBool isWin7 = PartyIsOsVersionWindows7();
        PCWSTR partyDllName = isWin7 ? L"PartyWin7.dll" : L"PartyWin.dll";

        HMODULE partyDll = LoadLibraryExW(partyDllName, NULL, 0);
        if (partyDll == NULL)
        {
            return c_partyErrorFailedLoadingPartyModule;
        }

        if (PARTY_FAILED(PartyLoadWindowsDllExports(partyDll, &s_partyFunctions)))
        {
            FreeLibrary(partyDll);
            ZeroMemory(&s_partyFunctions, sizeof(s_partyFunctions));
            return c_partyErrorFailedLoadingPartyModule;
        }

        // Deliberately do not free the partyDll. It has been loaded and will be used for the rest
        // of the process lifetime, just as if the program had linked against its import library.
    }

    *partyFunctions = &s_partyFunctions;
    return c_partyErrorSuccess;
}

// BEGIN GENERATED SECTION (definitions): DO NOT EDIT

inline
PartyError
PARTY_API
PartyLocalUserGetEntityId(
    PARTY_LOCAL_USER_HANDLE localUser,
    _Outptr_ PartyString* entityId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyLocalUserGetEntityId(localUser, entityId);
}

inline
PartyError
PARTY_API
PartyLocalUserUpdateEntityToken(
    PARTY_LOCAL_USER_HANDLE localUser,
    PartyString titlePlayerEntityToken
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyLocalUserUpdateEntityToken(localUser, titlePlayerEntityToken);
}

inline
PartyError
PARTY_API
PartyLocalUserGetCustomContext(
    PARTY_LOCAL_USER_HANDLE localUser,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyLocalUserGetCustomContext(localUser, customContext);
}

inline
PartyError
PARTY_API
PartyLocalUserSetCustomContext(
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyLocalUserSetCustomContext(localUser, customContext);
}

inline
PartyError
PARTY_API
PartyEndpointGetLocalUser(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_result_maybenull_ PARTY_LOCAL_USER_HANDLE* localUser
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetLocalUser(endpoint, localUser);
}

inline
PartyError
PARTY_API
PartyEndpointSendMessage(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints,
    PARTY_SEND_MESSAGE_OPTIONS options,
    _In_opt_ const PARTY_SEND_MESSAGE_QUEUING_CONFIGURATION* queuingConfiguration,
    uint32_t dataBufferCount,
    _In_reads_(dataBufferCount) const PARTY_DATA_BUFFER* dataBuffers,
    _In_opt_ void* messageIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointSendMessage(endpoint, targetEndpointCount, targetEndpoints, options, queuingConfiguration, dataBufferCount, dataBuffers, messageIdentifier);
}

inline
PartyError
PARTY_API
PartyEndpointCancelMessages(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints,
    PARTY_CANCEL_MESSAGES_FILTER_EXPRESSION filterExpression,
    uint32_t messageIdentityFilterMask,
    uint32_t filteredMessageIdentitiesToMatch,
    _Out_opt_ uint32_t* canceledMessagesCount
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointCancelMessages(endpoint, targetEndpointCount, targetEndpoints, filterExpression, messageIdentityFilterMask, filteredMessageIdentitiesToMatch, canceledMessagesCount);
}

inline
PartyError
PARTY_API
PartyEndpointFlushMessages(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointFlushMessages(endpoint, targetEndpointCount, targetEndpoints);
}

inline
PartyError
PARTY_API
PartyEndpointGetEndpointStatistics(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t targetEndpointCount,
    _In_reads_(targetEndpointCount) const PARTY_ENDPOINT_HANDLE* targetEndpoints,
    uint32_t statisticCount,
    _In_reads_(statisticCount) const PARTY_ENDPOINT_STATISTIC* statisticTypes,
    _Out_writes_all_(statisticCount) uint64_t* statisticValues
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetEndpointStatistics(endpoint, targetEndpointCount, targetEndpoints, statisticCount, statisticTypes, statisticValues);
}

inline
PartyError
PARTY_API
PartyEndpointIsLocal(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Out_ PartyBool* isLocal
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointIsLocal(endpoint, isLocal);
}

inline
PartyError
PARTY_API
PartyEndpointGetEntityId(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_result_maybenull_ PartyString* entityId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetEntityId(endpoint, entityId);
}

inline
PartyError
PARTY_API
PartyEndpointGetNetwork(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_ PARTY_NETWORK_HANDLE* network
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetNetwork(endpoint, network);
}

inline
PartyError
PARTY_API
PartyEndpointGetDevice(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_ PARTY_DEVICE_HANDLE* device
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetDevice(endpoint, device);
}

inline
PartyError
PARTY_API
PartyEndpointGetUniqueIdentifier(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Out_ uint16_t* uniqueIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetUniqueIdentifier(endpoint, uniqueIdentifier);
}

inline
PartyError
PARTY_API
PartyEndpointGetSharedProperty(
    PARTY_ENDPOINT_HANDLE endpoint,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetSharedProperty(endpoint, key, value);
}

inline
PartyError
PARTY_API
PartyEndpointGetSharedPropertyKeys(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetSharedPropertyKeys(endpoint, propertyCount, keys);
}

inline
PartyError
PARTY_API
PartyEndpointSetSharedProperties(
    PARTY_ENDPOINT_HANDLE endpoint,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointSetSharedProperties(endpoint, propertyCount, keys, values);
}

inline
PartyError
PARTY_API
PartyEndpointGetCustomContext(
    PARTY_ENDPOINT_HANDLE endpoint,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointGetCustomContext(endpoint, customContext);
}

inline
PartyError
PARTY_API
PartyEndpointSetCustomContext(
    PARTY_ENDPOINT_HANDLE endpoint,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyEndpointSetCustomContext(endpoint, customContext);
}

inline
PartyError
PARTY_API
PartyDeviceCreateChatControl(
    PARTY_DEVICE_HANDLE device,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ PartyString languageCode,
    _In_opt_ void* asyncIdentifier,
    _Outptr_opt_ PARTY_CHAT_CONTROL_HANDLE* chatControl
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceCreateChatControl(device, localUser, languageCode, asyncIdentifier, chatControl);
}

inline
PartyError
PARTY_API
PartyDeviceDestroyChatControl(
    PARTY_DEVICE_HANDLE device,
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceDestroyChatControl(device, chatControl, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyDeviceIsLocal(
    PARTY_DEVICE_HANDLE device,
    _Out_ PartyBool* isLocal
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceIsLocal(device, isLocal);
}

inline
PartyError
PARTY_API
PartyDeviceGetChatControls(
    PARTY_DEVICE_HANDLE device,
    _Out_ uint32_t* chatControlCount,
    _Outptr_result_buffer_(*chatControlCount) const PARTY_CHAT_CONTROL_HANDLE** chatControls
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceGetChatControls(device, chatControlCount, chatControls);
}

inline
PartyError
PARTY_API
PartyDeviceGetSharedProperty(
    PARTY_DEVICE_HANDLE device,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceGetSharedProperty(device, key, value);
}

inline
PartyError
PARTY_API
PartyDeviceGetSharedPropertyKeys(
    PARTY_DEVICE_HANDLE device,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceGetSharedPropertyKeys(device, propertyCount, keys);
}

inline
PartyError
PARTY_API
PartyDeviceSetSharedProperties(
    PARTY_DEVICE_HANDLE device,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceSetSharedProperties(device, propertyCount, keys, values);
}

inline
PartyError
PARTY_API
PartyDeviceGetCustomContext(
     PARTY_DEVICE_HANDLE device,
     _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceGetCustomContext(device, customContext);
}

inline
PartyError
PARTY_API
PartyDeviceSetCustomContext(
    PARTY_DEVICE_HANDLE device,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeviceSetCustomContext(device, customContext);
}

inline
PartyError
PARTY_API
PartyInvitationGetCreatorEntityId(
    PARTY_INVITATION_HANDLE invitation,
    _Outptr_result_maybenull_ PartyString * entityId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyInvitationGetCreatorEntityId(invitation, entityId);
}

inline
PartyError
PARTY_API
PartyInvitationGetInvitationConfiguration(
    PARTY_INVITATION_HANDLE invitation,
    _Outptr_ const PARTY_INVITATION_CONFIGURATION ** configuration
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyInvitationGetInvitationConfiguration(invitation, configuration);
}

inline
PartyError
PARTY_API
PartyInvitationGetCustomContext(
    PARTY_INVITATION_HANDLE invitation,
    _Outptr_result_maybenull_ void ** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyInvitationGetCustomContext(invitation, customContext);
}

inline
PartyError
PARTY_API
PartyInvitationSetCustomContext(
    PARTY_INVITATION_HANDLE invitation,
    _In_opt_ void * customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyInvitationSetCustomContext(invitation, customContext);
}

inline
PartyError
PARTY_API
PartyNetworkAuthenticateLocalUser(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    PartyString invitationIdentifier,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkAuthenticateLocalUser(network, localUser, invitationIdentifier, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkRemoveLocalUser(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkRemoveLocalUser(network, localUser, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkCreateInvitation(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ const PARTY_INVITATION_CONFIGURATION* invitationConfiguration,
    void* asyncIdentifier,
    _Outptr_opt_ PARTY_INVITATION_HANDLE* invitation
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkCreateInvitation(network, localUser, invitationConfiguration, asyncIdentifier, invitation);
}

inline
PartyError
PARTY_API
PartyNetworkRevokeInvitation(
    PARTY_NETWORK_HANDLE network,
    PARTY_LOCAL_USER_HANDLE localUser,
    PARTY_INVITATION_HANDLE invitation,
    void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkRevokeInvitation(network, localUser, invitation, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkGetInvitations(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* invitationCount,
    _Outptr_result_buffer_(*invitationCount) const PARTY_INVITATION_HANDLE** invitations
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetInvitations(network, invitationCount, invitations);
}

inline
PartyError
PARTY_API
PartyNetworkCreateEndpoint(
    PARTY_NETWORK_HANDLE network,
    _In_opt_ PARTY_LOCAL_USER_HANDLE localUser,
    uint32_t sharedPropertyCount,
    _In_reads_opt_(sharedPropertyCount) const PartyString* keys,
    _In_reads_opt_(sharedPropertyCount) const PARTY_DATA_BUFFER* values,
    _In_opt_ void* asyncIdentifier,
    _Outptr_opt_ PARTY_ENDPOINT_HANDLE* endpoint
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkCreateEndpoint(network, localUser, sharedPropertyCount, keys, values, asyncIdentifier, endpoint);
}

inline
PartyError
PARTY_API
PartyNetworkDestroyEndpoint(
    PARTY_NETWORK_HANDLE network,
    PARTY_ENDPOINT_HANDLE localEndpoint,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkDestroyEndpoint(network, localEndpoint, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkLeaveNetwork(
    PARTY_NETWORK_HANDLE network,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkLeaveNetwork(network, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkGetEndpoints(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* endpointCount,
    _Outptr_result_buffer_(*endpointCount) const PARTY_ENDPOINT_HANDLE** endpoints
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetEndpoints(network, endpointCount, endpoints);
}

inline
PartyError
PARTY_API
PartyNetworkFindEndpointByUniqueIdentifier(
    PARTY_NETWORK_HANDLE network,
    uint16_t uniqueIdentifier,
    _Outptr_ PARTY_ENDPOINT_HANDLE* endpoint
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkFindEndpointByUniqueIdentifier(network, uniqueIdentifier, endpoint);
}

inline
PartyError
PARTY_API
PartyNetworkGetDevices(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* deviceCount,
    _Outptr_result_buffer_(*deviceCount) const PARTY_DEVICE_HANDLE** devices
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetDevices(network, deviceCount, devices);
}

inline
PartyError
PARTY_API
PartyNetworkGetLocalUsers(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* userCount,
    _Outptr_result_buffer_(*userCount) const PARTY_LOCAL_USER_HANDLE** users
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetLocalUsers(network, userCount, users);
}

inline
PartyError
PARTY_API
PartyNetworkGetNetworkDescriptor(
     PARTY_NETWORK_HANDLE network,
     _Out_ PARTY_NETWORK_DESCRIPTOR* networkDescriptor
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetNetworkDescriptor(network, networkDescriptor);
}

inline
PartyError
PARTY_API
PartyNetworkGetNetworkConfiguration(
    PARTY_NETWORK_HANDLE network,
    _Outptr_ const PARTY_NETWORK_CONFIGURATION** networkConfiguration
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetNetworkConfiguration(network, networkConfiguration);
}

inline
PartyError
PARTY_API
PartyNetworkKickDevice(
    PARTY_NETWORK_HANDLE network,
    PARTY_DEVICE_HANDLE targetDevice,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkKickDevice(network, targetDevice, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkKickUser(
    PARTY_NETWORK_HANDLE network,
    PartyString targetEntityId,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkKickUser(network, targetEntityId, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkGetSharedProperty(
    PARTY_NETWORK_HANDLE network,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetSharedProperty(network, key, value);
}

inline
PartyError
PARTY_API
PartyNetworkGetSharedPropertyKeys(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetSharedPropertyKeys(network, propertyCount, keys);
}

inline
PartyError
PARTY_API
PartyNetworkSetSharedProperties(
    PARTY_NETWORK_HANDLE network,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkSetSharedProperties(network, propertyCount, keys, values);
}

inline
PartyError
PARTY_API
PartyNetworkConnectChatControl(
    PARTY_NETWORK_HANDLE network,
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkConnectChatControl(network, chatControl, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkDisconnectChatControl(
    PARTY_NETWORK_HANDLE network,
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkDisconnectChatControl(network, chatControl, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyNetworkGetChatControls(
    PARTY_NETWORK_HANDLE network,
    _Out_ uint32_t* chatControlCount,
    _Outptr_result_buffer_(*chatControlCount) const PARTY_CHAT_CONTROL_HANDLE** chatControls
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetChatControls(network, chatControlCount, chatControls);
}

inline
PartyError
PARTY_API
PartyNetworkGetNetworkStatistics(
    PARTY_NETWORK_HANDLE network,
    uint32_t statisticCount,
    _In_reads_(statisticCount) const PARTY_NETWORK_STATISTIC* statisticTypes,
    _Out_writes_all_(statisticCount) uint64_t* statisticValues
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetNetworkStatistics(network, statisticCount, statisticTypes, statisticValues);
}

inline
PartyError
PARTY_API
PartyNetworkGetCustomContext(
    PARTY_NETWORK_HANDLE network,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetCustomContext(network, customContext);
}

inline
PartyError
PARTY_API
PartyNetworkSetCustomContext(
    PARTY_NETWORK_HANDLE network,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkSetCustomContext(network, customContext);
}

inline
PartyError
PARTY_API
PartyNetworkGetDeviceConnectionType(
    PARTY_NETWORK_HANDLE network,
    PARTY_DEVICE_HANDLE targetDevice,
    _Out_ PARTY_DEVICE_CONNECTION_TYPE* deviceConnectionType
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyNetworkGetDeviceConnectionType(network, targetDevice, deviceConnectionType);
}

inline
PartyError
PARTY_API
PartyChatControlGetLocalUser(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_LOCAL_USER_HANDLE* localUser
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetLocalUser(chatControl, localUser);
}

inline
PartyError
PARTY_API
PartyChatControlSetPermissions(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    PARTY_CHAT_PERMISSION_OPTIONS chatPermissionOptions
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetPermissions(chatControl, targetChatControl, chatPermissionOptions);
}

inline
PartyError
PARTY_API
PartyChatControlGetPermissions(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PARTY_CHAT_PERMISSION_OPTIONS* chatPermissionOptions
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetPermissions(chatControl, targetChatControl, chatPermissionOptions);
}

inline
PartyError
PARTY_API
PartyChatControlSendText(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    uint32_t targetChatControlCount,
    _In_reads_(targetChatControlCount) const PARTY_CHAT_CONTROL_HANDLE* targetChatControls,
    PartyString chatText,
    uint32_t dataBufferCount,
    _In_reads_(dataBufferCount) const PARTY_DATA_BUFFER* dataBuffers
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSendText(chatControl, targetChatControlCount, targetChatControls, chatText, dataBufferCount, dataBuffers);
}

inline
PartyError
PARTY_API
PartyChatControlSetAudioInput(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_AUDIO_DEVICE_SELECTION_TYPE audioDeviceSelectionType,
    _In_opt_ PartyString audioDeviceSelectionContext,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetAudioInput(chatControl, audioDeviceSelectionType, audioDeviceSelectionContext, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioInput(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_AUDIO_DEVICE_SELECTION_TYPE* audioDeviceSelectionType,
    _Outptr_ PartyString* audioDeviceSelectionContext,
    _Outptr_ PartyString* deviceId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioInput(chatControl, audioDeviceSelectionType, audioDeviceSelectionContext, deviceId);
}

inline
PartyError
PARTY_API
PartyChatControlSetAudioOutput(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_AUDIO_DEVICE_SELECTION_TYPE audioDeviceSelectionType,
    _In_opt_ PartyString audioDeviceSelectionContext,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetAudioOutput(chatControl, audioDeviceSelectionType, audioDeviceSelectionContext, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioOutput(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_AUDIO_DEVICE_SELECTION_TYPE* audioDeviceSelectionType,
    _Outptr_ PartyString* audioDeviceSelectionContext,
    _Outptr_ PartyString* deviceId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioOutput(chatControl, audioDeviceSelectionType, audioDeviceSelectionContext, deviceId);
}

inline
PartyError
PARTY_API
PartyChatControlPopulateAvailableTextToSpeechProfiles(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlPopulateAvailableTextToSpeechProfiles(chatControl, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAvailableTextToSpeechProfiles(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* profileCount,
    _Outptr_result_buffer_(*profileCount) const PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE** profiles
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAvailableTextToSpeechProfiles(chatControl, profileCount, profiles);
}

inline
PartyError
PARTY_API
PartyChatControlSetTextToSpeechProfile(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_SYNTHESIZE_TEXT_TO_SPEECH_TYPE type,
    _In_opt_ PartyString profileIdentifier,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetTextToSpeechProfile(chatControl, type, profileIdentifier, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetTextToSpeechProfile(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_SYNTHESIZE_TEXT_TO_SPEECH_TYPE type,
    _Outptr_result_maybenull_ PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE* profile
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetTextToSpeechProfile(chatControl, type, profile);
}

inline
PartyError
PARTY_API
PartyChatControlSynthesizeTextToSpeech(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_SYNTHESIZE_TEXT_TO_SPEECH_TYPE type,
    PartyString textToSynthesize,
    _In_opt_ void * asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSynthesizeTextToSpeech(chatControl, type, textToSynthesize, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlSetLanguage(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PartyString languageCode,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetLanguage(chatControl, languageCode, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetLanguage(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PartyString* languageCode
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetLanguage(chatControl, languageCode);
}

inline
PartyError
PARTY_API
PartyChatControlSetTranscriptionOptions(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_VOICE_CHAT_TRANSCRIPTION_OPTIONS options,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetTranscriptionOptions(chatControl, options, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetTranscriptionOptions(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_VOICE_CHAT_TRANSCRIPTION_OPTIONS* options
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetTranscriptionOptions(chatControl, options);
}

inline
PartyError
PARTY_API
PartyChatControlSetTextChatOptions(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_TEXT_CHAT_OPTIONS options,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetTextChatOptions(chatControl, options, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetTextChatOptions(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_TEXT_CHAT_OPTIONS* options
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetTextChatOptions(chatControl, options);
}

inline
PartyError
PARTY_API
PartyChatControlSetAudioRenderVolume(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    float volume
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetAudioRenderVolume(chatControl, targetChatControl, volume);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioRenderVolume(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ float* volume
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioRenderVolume(chatControl, targetChatControl, volume);
}

inline
PartyError
PARTY_API
PartyChatControlSetAudioInputMuted(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PartyBool muted
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetAudioInputMuted(chatControl, muted);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioInputMuted(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PartyBool* muted
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioInputMuted(chatControl, muted);
}

inline
PartyError
PARTY_API
PartyChatControlSetIncomingAudioMuted(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    PartyBool muted
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetIncomingAudioMuted(chatControl, targetChatControl, muted);
}

inline
PartyError
PARTY_API
PartyChatControlGetIncomingAudioMuted(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PartyBool* muted
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetIncomingAudioMuted(chatControl, targetChatControl, muted);
}

inline
PartyError
PARTY_API
PartyChatControlSetIncomingTextMuted(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    PartyBool muted
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetIncomingTextMuted(chatControl, targetChatControl, muted);
}

inline
PartyError
PARTY_API
PartyChatControlGetIncomingTextMuted(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PartyBool* muted
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetIncomingTextMuted(chatControl, targetChatControl, muted);
}

inline
PartyError
PARTY_API
PartyChatControlGetLocalChatIndicator(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PARTY_LOCAL_CHAT_CONTROL_CHAT_INDICATOR* chatIndicator
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetLocalChatIndicator(chatControl, chatIndicator);
}

inline
PartyError
PARTY_API
PartyChatControlGetChatIndicator(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PARTY_CHAT_CONTROL_HANDLE targetChatControl,
    _Out_ PARTY_CHAT_CONTROL_CHAT_INDICATOR* chatIndicator
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetChatIndicator(chatControl, targetChatControl, chatIndicator);
}

inline
PartyError
PARTY_API
PartyChatControlSetAudioEncoderBitrate(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    uint32_t bitrate,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetAudioEncoderBitrate(chatControl, bitrate, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioEncoderBitrate(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* bitrate
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioEncoderBitrate(chatControl, bitrate);
}

inline
PartyError
PARTY_API
PartyChatControlIsLocal(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ PartyBool* isLocal
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlIsLocal(chatControl, isLocal);
}

inline
PartyError
PARTY_API
PartyChatControlGetDevice(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_DEVICE_HANDLE* device
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetDevice(chatControl, device);
}

inline
PartyError
PARTY_API
PartyChatControlGetEntityId(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PartyString* entityId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetEntityId(chatControl, entityId);
}

inline
PartyError
PARTY_API
PartyChatControlGetSharedProperty(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    PartyString key,
    _Out_ PARTY_DATA_BUFFER* value
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetSharedProperty(chatControl, key, value);
}

inline
PartyError
PARTY_API
PartyChatControlGetSharedPropertyKeys(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* propertyCount,
    _Outptr_result_buffer_(*propertyCount) const PartyString** keys
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetSharedPropertyKeys(chatControl, propertyCount, keys);
}

inline
PartyError
PARTY_API
PartyChatControlSetSharedProperties(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    uint32_t propertyCount,
    _In_reads_(propertyCount) const PartyString* keys,
    _In_reads_(propertyCount) const PARTY_DATA_BUFFER* values
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetSharedProperties(chatControl, propertyCount, keys, values);
}

inline
PartyError
PARTY_API
PartyChatControlGetNetworks(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Out_ uint32_t* networkCount,
    _Outptr_result_buffer_(*networkCount) const PARTY_NETWORK_HANDLE** networks
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetNetworks(chatControl, networkCount, networks);
}

inline
PartyError
PARTY_API
PartyChatControlSetCustomContext(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlSetCustomContext(chatControl, customContext);
}

inline
PartyError
PARTY_API
PartyChatControlGetCustomContext(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetCustomContext(chatControl, customContext);
}

inline
PartyError
PARTY_API
PartyChatControlConfigureAudioManipulationVoiceStream(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_CONFIGURATION* configuration,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlConfigureAudioManipulationVoiceStream(chatControl, configuration, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioManipulationVoiceStream(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE* stream
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioManipulationVoiceStream(chatControl, stream);
}

inline
PartyError
PARTY_API
PartyChatControlConfigureAudioManipulationCaptureStream(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_CONFIGURATION* configuration,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlConfigureAudioManipulationCaptureStream(chatControl, configuration, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioManipulationCaptureStream(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE* stream
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioManipulationCaptureStream(chatControl, stream);
}

inline
PartyError
PARTY_API
PartyChatControlConfigureAudioManipulationRenderStream(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _In_opt_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_CONFIGURATION* configuration,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlConfigureAudioManipulationRenderStream(chatControl, configuration, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyChatControlGetAudioManipulationRenderStream(
    PARTY_CHAT_CONTROL_HANDLE chatControl,
    _Outptr_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE* stream
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyChatControlGetAudioManipulationRenderStream(chatControl, stream);
}

inline
PartyError
PARTY_API
PartyTextToSpeechProfileGetIdentifier(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_ PartyString* identifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyTextToSpeechProfileGetIdentifier(profile, identifier);
}

inline
PartyError
PARTY_API
PartyTextToSpeechProfileGetName(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_ PartyString* name
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyTextToSpeechProfileGetName(profile, name);
}

inline
PartyError
PARTY_API
PartyTextToSpeechProfileGetLanguageCode(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_ PartyString* languageCode
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyTextToSpeechProfileGetLanguageCode(profile, languageCode);
}

inline
PartyError
PARTY_API
PartyTextToSpeechProfileGetGender(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Out_ PARTY_GENDER* gender
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyTextToSpeechProfileGetGender(profile, gender);
}

inline
PartyError
PARTY_API
PartyTextToSpeechProfileGetCustomContext(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyTextToSpeechProfileGetCustomContext(profile, customContext);
}

inline
PartyError
PARTY_API
PartyTextToSpeechProfileSetCustomContext(
    PARTY_TEXT_TO_SPEECH_PROFILE_HANDLE profile,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyTextToSpeechProfileSetCustomContext(profile, customContext);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamGetConfiguration(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_CONFIGURATION * configuration
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamGetConfiguration(stream, configuration);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamGetFormat(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_FORMAT * format
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamGetFormat(stream, format);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamGetAvailableBufferCount(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ uint32_t* count
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamGetAvailableBufferCount(stream, count);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamGetNextBuffer(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Out_ PARTY_MUTABLE_DATA_BUFFER* buffer
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamGetNextBuffer(stream, buffer);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamReturnBuffer(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Post_invalid_ void * buffer
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamReturnBuffer(stream, buffer);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamGetCustomContext(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamGetCustomContext(stream, customContext);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSourceStreamSetCustomContext(
    PARTY_AUDIO_MANIPULATION_SOURCE_STREAM_HANDLE stream,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSourceStreamSetCustomContext(stream, customContext);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSinkStreamGetConfiguration(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_MANIPULATION_SINK_STREAM_CONFIGURATION * configuration
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSinkStreamGetConfiguration(stream, configuration);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSinkStreamGetFormat(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _Out_ PARTY_AUDIO_FORMAT* format
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSinkStreamGetFormat(stream, format);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSinkStreamSubmitBuffer(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    const PARTY_DATA_BUFFER* buffer
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSinkStreamSubmitBuffer(stream, buffer);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSinkStreamGetCustomContext(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _Outptr_result_maybenull_ void** customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSinkStreamGetCustomContext(stream, customContext);
}

inline
PartyError
PARTY_API
PartyAudioManipulationSinkStreamSetCustomContext(
    PARTY_AUDIO_MANIPULATION_SINK_STREAM_HANDLE stream,
    _In_opt_ void* customContext
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyAudioManipulationSinkStreamSetCustomContext(stream, customContext);
}

inline
PartyError
PARTY_API
PartySetOption(
    _In_opt_ void* object,
    PARTY_OPTION option,
    _In_opt_ const void* value
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySetOption(object, option, value);
}

inline
PartyError
PARTY_API
PartyGetOption(
    _In_opt_ const void* object,
    PARTY_OPTION option,
    _Out_ void* value
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetOption(object, option, value);
}

inline
PartyError
PARTY_API
PartyGetErrorMessage(
    PartyError error,
    _Outptr_ PartyString* errorMessage
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetErrorMessage(error, errorMessage);
}

inline
PartyError
PARTY_API
PartySerializeNetworkDescriptor(
    const PARTY_NETWORK_DESCRIPTOR* networkDescriptor,
    _Out_writes_z_(PARTY_MAX_SERIALIZED_NETWORK_DESCRIPTOR_STRING_LENGTH + 1) char* serializedNetworkDescriptorString
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySerializeNetworkDescriptor(networkDescriptor, serializedNetworkDescriptorString);
}

inline
PartyError
PARTY_API
PartyDeserializeNetworkDescriptor(
    PartyString serializedNetworkDescriptorString,
    _Out_ PARTY_NETWORK_DESCRIPTOR* networkDescriptor
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDeserializeNetworkDescriptor(serializedNetworkDescriptorString, networkDescriptor);
}

inline
PartyError
PARTY_API
PartySetMemoryCallbacks(
    _In_ PARTY_MEM_ALLOC_FUNC allocateMemoryCallback,
    _In_ PARTY_MEM_FREE_FUNC freeMemoryCallback
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySetMemoryCallbacks(allocateMemoryCallback, freeMemoryCallback);
}

inline
PartyError
PARTY_API
PartyGetMemoryCallbacks(
    _Out_ PARTY_MEM_ALLOC_FUNC* allocateMemoryCallback,
    _Out_ PARTY_MEM_FREE_FUNC* freeMemoryCallback
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetMemoryCallbacks(allocateMemoryCallback, freeMemoryCallback);
}

inline
PartyError
PARTY_API
PartySetProfilingCallbacksForMethodEntryExit(
    _In_opt_ PARTY_PROFILING_METHOD_ENTRANCE_FUNC profilingMethodEntranceCallback,
    _In_opt_ PARTY_PROFILING_METHOD_EXIT_FUNC profilingMethodExitCallback
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySetProfilingCallbacksForMethodEntryExit(profilingMethodEntranceCallback, profilingMethodExitCallback);
}

inline
PartyError
PARTY_API
PartyGetProfilingCallbacksForMethodEntryExit(
    _Outptr_result_maybenull_ PARTY_PROFILING_METHOD_ENTRANCE_FUNC* profilingMethodEntranceCallback,
    _Outptr_result_maybenull_ PARTY_PROFILING_METHOD_EXIT_FUNC* profilingMethodExitCallback
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetProfilingCallbacksForMethodEntryExit(profilingMethodEntranceCallback, profilingMethodExitCallback);
}

inline
PartyError
PARTY_API
PartySetThreadAffinityMask(
    PARTY_THREAD_ID threadId,
    uint64_t threadAffinityMask
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySetThreadAffinityMask(threadId, threadAffinityMask);
}

inline
PartyError
PARTY_API
PartyGetThreadAffinityMask(
    PARTY_THREAD_ID threadId,
    _Out_ uint64_t* threadAffinityMask
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetThreadAffinityMask(threadId, threadAffinityMask);
}

inline
PartyError
PARTY_API
PartySetWorkMode(
    PARTY_THREAD_ID threadId,
    PARTY_WORK_MODE workMode
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySetWorkMode(threadId, workMode);
}

inline
PartyError
PARTY_API
PartyGetWorkMode(
    PARTY_THREAD_ID threadId,
    _Out_ PARTY_WORK_MODE * workMode
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetWorkMode(threadId, workMode);
}

inline
PartyError
PARTY_API
PartyInitialize(
    PartyString titleId,
    _Outptr_ PARTY_HANDLE* handle
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyInitialize(titleId, handle);
}

inline
PartyError
PARTY_API
PartyCleanup(
    _Post_invalid_ PARTY_HANDLE handle
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyCleanup(handle);
}

inline
PartyError
PARTY_API
PartyStartProcessingStateChanges(
    PARTY_HANDLE handle,
    _Out_ uint32_t* stateChangeCount,
    _Outptr_result_buffer_(*stateChangeCount) const PARTY_STATE_CHANGE*const** stateChanges
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyStartProcessingStateChanges(handle, stateChangeCount, stateChanges);
}

inline
PartyError
PARTY_API
PartyFinishProcessingStateChanges(
    PARTY_HANDLE handle,
    uint32_t stateChangeCount,
    _In_reads_(stateChangeCount) const PARTY_STATE_CHANGE*const* stateChanges
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyFinishProcessingStateChanges(handle, stateChangeCount, stateChanges);
}

inline
PartyError
PARTY_API
PartyDoWork(
    PARTY_HANDLE handle,
    PARTY_THREAD_ID threadId
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDoWork(handle, threadId);
}

inline
PartyError
PARTY_API
PartyGetRegions(
    PARTY_HANDLE handle,
    _Out_ uint32_t* regionListCount,
    _Outptr_result_buffer_(*regionListCount) const PARTY_REGION** regionList
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetRegions(handle, regionListCount, regionList);
}

inline
PartyError
PARTY_API
PartyCreateNewNetwork(
    PARTY_HANDLE handle,
    PARTY_LOCAL_USER_HANDLE localUser,
    const PARTY_NETWORK_CONFIGURATION* networkConfiguration,
    uint32_t regionCount,
    _In_reads_(regionCount) const PARTY_REGION* regions,
    _In_opt_ const PARTY_INVITATION_CONFIGURATION* initialInvitationConfiguration,
    _In_opt_ void * asyncIdentifier,
    _Out_opt_ PARTY_NETWORK_DESCRIPTOR* networkDescriptor,
    _Out_writes_opt_z_(PARTY_MAX_INVITATION_IDENTIFIER_STRING_LENGTH + 1) char * appliedInitialInvitationIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyCreateNewNetwork(handle, localUser, networkConfiguration, regionCount, regions, initialInvitationConfiguration, asyncIdentifier, networkDescriptor, appliedInitialInvitationIdentifier);
}

inline
PartyError
PARTY_API
PartyConnectToNetwork(
    PARTY_HANDLE handle,
    const PARTY_NETWORK_DESCRIPTOR* networkDescriptor,
    _In_opt_ void* asyncIdentifier,
    _Outptr_opt_ PARTY_NETWORK_HANDLE* network
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyConnectToNetwork(handle, networkDescriptor, asyncIdentifier, network);
}

inline
PartyError
PARTY_API
PartySynchronizeMessagesBetweenEndpoints(
    PARTY_HANDLE handle,
    uint32_t endpointCount,
    _In_reads_(endpointCount) const PARTY_ENDPOINT_HANDLE* endpoints,
    PARTY_SYNCHRONIZE_MESSAGES_BETWEEN_ENDPOINTS_OPTIONS options,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartySynchronizeMessagesBetweenEndpoints(handle, endpointCount, endpoints, options, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyGetLocalDevice(
    PARTY_HANDLE handle,
    _Outptr_ PARTY_DEVICE_HANDLE* localDevice
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetLocalDevice(handle, localDevice);
}

inline
PartyError
PARTY_API
PartyCreateLocalUser(
    PARTY_HANDLE handle,
    PartyString entityId,
    PartyString titlePlayerEntityToken,
    _Outptr_ PARTY_LOCAL_USER_HANDLE* localUser
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyCreateLocalUser(handle, entityId, titlePlayerEntityToken, localUser);
}

inline
PartyError
PARTY_API
PartyDestroyLocalUser(
    PARTY_HANDLE handle,
    PARTY_LOCAL_USER_HANDLE localUser,
    _In_opt_ void* asyncIdentifier
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyDestroyLocalUser(handle, localUser, asyncIdentifier);
}

inline
PartyError
PARTY_API
PartyGetLocalUsers(
    PARTY_HANDLE handle,
    _Out_ uint32_t* userCount,
    _Outptr_result_buffer_(*userCount) const PARTY_LOCAL_USER_HANDLE** users
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetLocalUsers(handle, userCount, users);
}

inline
PartyError
PARTY_API
PartyGetNetworks(
    PARTY_HANDLE handle,
    _Out_ uint32_t* networkCount,
    _Outptr_result_buffer_(*networkCount) const PARTY_NETWORK_HANDLE** networks
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetNetworks(handle, networkCount, networks);
}

inline
PartyError
PARTY_API
PartyGetChatControls(
    PARTY_HANDLE handle,
    _Out_ uint32_t* chatControlCount,
    _Outptr_result_buffer_(*chatControlCount) const PARTY_CHAT_CONTROL_HANDLE** chatControls
    )
{
    const PARTY_FUNCTIONS* partyFunctions;
    PartyError getWindowsDllExportsError = PartyGetWindowsDllExports(&partyFunctions);
    if (PARTY_FAILED(getWindowsDllExportsError))
    {
        return getWindowsDllExportsError;
    }

    return partyFunctions->FunctionTable.PartyGetChatControls(handle, chatControlCount, chatControls);
}

// END GENERATED SECTION

#ifdef __cplusplus
}
#pragma warning(pop)
#endif
