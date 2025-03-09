

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from test20241026IDL.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef test20241026IDLPlugin_140137780_h
#define test20241026IDLPlugin_140137780_h

#include "test20241026IDL.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

extern "C" {

    #define HelloWorldPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define HelloWorldPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define HelloWorldPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define HelloWorldPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define HelloWorldPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern HelloWorld*
    HelloWorldPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern HelloWorld*
    HelloWorldPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern HelloWorld*
    HelloWorldPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPluginSupport_copy_data(
        HelloWorld *out,
        const HelloWorld *in);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_destroy_data_w_params(
        HelloWorld *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_destroy_data_ex(
        HelloWorld *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_destroy_data(
        HelloWorld *sample);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_print_data(
        const HelloWorld *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    HelloWorldPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    HelloWorldPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    HelloWorldPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    HelloWorldPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    HelloWorldPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld *out,
        const HelloWorld *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const HelloWorld *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const HelloWorld *sample); 

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_deserialize_from_cdr_buffer(
        HelloWorld *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    HelloWorldPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const HelloWorld * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    HelloWorldPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const HelloWorld *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    HelloWorldPlugin_new(void);

    NDDSUSERDllExport extern void
    HelloWorldPlugin_delete(struct PRESTypePlugin *);

    #define PostDataPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define PostDataPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define PostDataPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define PostDataPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define PostDataPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PostData*
    PostDataPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern PostData*
    PostDataPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern PostData*
    PostDataPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    PostDataPluginSupport_copy_data(
        PostData *out,
        const PostData *in);

    NDDSUSERDllExport extern void 
    PostDataPluginSupport_destroy_data_w_params(
        PostData *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    PostDataPluginSupport_destroy_data_ex(
        PostData *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    PostDataPluginSupport_destroy_data(
        PostData *sample);

    NDDSUSERDllExport extern void 
    PostDataPluginSupport_print_data(
        const PostData *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    PostDataPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    PostDataPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    PostDataPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    PostDataPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    PostDataPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        PostData *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        PostData *out,
        const PostData *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const PostData *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        PostData *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PostDataPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const PostData *sample); 

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        PostData **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PostDataPlugin_deserialize_from_cdr_buffer(
        PostData *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    PostDataPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    PostDataPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    PostDataPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    PostDataPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    PostDataPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const PostData * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    PostDataPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    PostDataPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    PostDataPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const PostData *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        PostData * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PostDataPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        PostData ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PostDataPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        PostData *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    PostDataPlugin_new(void);

    NDDSUSERDllExport extern void
    PostDataPlugin_delete(struct PRESTypePlugin *);

    #define add_retPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define add_retPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define add_retPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define add_retPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define add_retPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern add_ret*
    add_retPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern add_ret*
    add_retPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern add_ret*
    add_retPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    add_retPluginSupport_copy_data(
        add_ret *out,
        const add_ret *in);

    NDDSUSERDllExport extern void 
    add_retPluginSupport_destroy_data_w_params(
        add_ret *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    add_retPluginSupport_destroy_data_ex(
        add_ret *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    add_retPluginSupport_destroy_data(
        add_ret *sample);

    NDDSUSERDllExport extern void 
    add_retPluginSupport_print_data(
        const add_ret *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    add_retPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    add_retPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    add_retPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    add_retPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    add_retPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_ret *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_ret *out,
        const add_ret *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const add_ret *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_ret *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    add_retPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const add_ret *sample); 

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        add_ret **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    add_retPlugin_deserialize_from_cdr_buffer(
        add_ret *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    add_retPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    add_retPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    add_retPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    add_retPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    add_retPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const add_ret * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    add_retPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    add_retPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    add_retPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const add_ret *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_ret * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    add_retPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        add_ret ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    add_retPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        add_ret *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    add_retPlugin_new(void);

    NDDSUSERDllExport extern void
    add_retPlugin_delete(struct PRESTypePlugin *);

    #define add_paramsPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define add_paramsPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define add_paramsPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define add_paramsPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define add_paramsPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern add_params*
    add_paramsPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern add_params*
    add_paramsPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern add_params*
    add_paramsPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    add_paramsPluginSupport_copy_data(
        add_params *out,
        const add_params *in);

    NDDSUSERDllExport extern void 
    add_paramsPluginSupport_destroy_data_w_params(
        add_params *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    add_paramsPluginSupport_destroy_data_ex(
        add_params *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    add_paramsPluginSupport_destroy_data(
        add_params *sample);

    NDDSUSERDllExport extern void 
    add_paramsPluginSupport_print_data(
        const add_params *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    add_paramsPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    add_paramsPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    add_paramsPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    add_paramsPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    add_paramsPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_params *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_params *out,
        const add_params *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const add_params *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_params *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    add_paramsPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const add_params *sample); 

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        add_params **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    add_paramsPlugin_deserialize_from_cdr_buffer(
        add_params *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    add_paramsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    add_paramsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    add_paramsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    add_paramsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    add_paramsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const add_params * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    add_paramsPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    add_paramsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    add_paramsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const add_params *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        add_params * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    add_paramsPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        add_params ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    add_paramsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        add_params *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    add_paramsPlugin_new(void);

    NDDSUSERDllExport extern void
    add_paramsPlugin_delete(struct PRESTypePlugin *);

    #define minus_retPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define minus_retPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define minus_retPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define minus_retPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define minus_retPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern minus_ret*
    minus_retPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern minus_ret*
    minus_retPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern minus_ret*
    minus_retPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    minus_retPluginSupport_copy_data(
        minus_ret *out,
        const minus_ret *in);

    NDDSUSERDllExport extern void 
    minus_retPluginSupport_destroy_data_w_params(
        minus_ret *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    minus_retPluginSupport_destroy_data_ex(
        minus_ret *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    minus_retPluginSupport_destroy_data(
        minus_ret *sample);

    NDDSUSERDllExport extern void 
    minus_retPluginSupport_print_data(
        const minus_ret *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    minus_retPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    minus_retPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    minus_retPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    minus_retPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    minus_retPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret *out,
        const minus_ret *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const minus_ret *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    minus_retPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const minus_ret *sample); 

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    minus_retPlugin_deserialize_from_cdr_buffer(
        minus_ret *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    minus_retPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    minus_retPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    minus_retPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    minus_retPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    minus_retPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const minus_ret * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    minus_retPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    minus_retPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    minus_retPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const minus_ret *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    minus_retPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    minus_retPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        minus_ret *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    minus_retPlugin_new(void);

    NDDSUSERDllExport extern void
    minus_retPlugin_delete(struct PRESTypePlugin *);

    #define minus_paramsPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define minus_paramsPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define minus_paramsPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define minus_paramsPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define minus_paramsPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern minus_params*
    minus_paramsPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern minus_params*
    minus_paramsPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern minus_params*
    minus_paramsPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPluginSupport_copy_data(
        minus_params *out,
        const minus_params *in);

    NDDSUSERDllExport extern void 
    minus_paramsPluginSupport_destroy_data_w_params(
        minus_params *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    minus_paramsPluginSupport_destroy_data_ex(
        minus_params *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    minus_paramsPluginSupport_destroy_data(
        minus_params *sample);

    NDDSUSERDllExport extern void 
    minus_paramsPluginSupport_print_data(
        const minus_params *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    minus_paramsPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    minus_paramsPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    minus_paramsPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    minus_paramsPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    minus_paramsPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_params *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_params *out,
        const minus_params *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const minus_params *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_params *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    minus_paramsPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const minus_params *sample); 

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        minus_params **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    minus_paramsPlugin_deserialize_from_cdr_buffer(
        minus_params *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    minus_paramsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    minus_paramsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    minus_paramsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    minus_paramsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    minus_paramsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const minus_params * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    minus_paramsPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    minus_paramsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    minus_paramsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const minus_params *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        minus_params * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    minus_paramsPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        minus_params ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    minus_paramsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        minus_params *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    minus_paramsPlugin_new(void);

    NDDSUSERDllExport extern void
    minus_paramsPlugin_delete(struct PRESTypePlugin *);

}

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* test20241026IDLPlugin_140137780_h */

