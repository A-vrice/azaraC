// Top-level JSON serializer entry point

#include "azaraC.h"
#include "JsonSerializer.h"
#include "JsonWriter.h"
#include "definition/_index.h"
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif

namespace azaraC {
namespace internal {

// Forward declarations (defined in separate files)
#if (AZARAC_ENABLE_DCX_CAMF)
void serializeDcx(const Message& m, Print& out);
#endif
#if (AZARAC_ENABLE_EEW)
bool serializeEEW(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
bool serializeHypocenter(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_SEISMIC)
bool serializeSeismic(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_NANKAI)
bool serializeNankai(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_TSUNAMI)
bool serializeTsunami(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
bool serializeNwPacTsu(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_VOLCANO)
bool serializeVolcano(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_ASH_FALL)
bool serializeAshFall(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_WEATHER)
bool serializeWeather(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_FLOOD)
bool serializeFlood(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_TYPHOON)
bool serializeTyphoon(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_MARINE)
bool serializeMarine(const Mt43Data* d, Print& out);
#endif

// Top-level serialize
void JsonSerializer::serialize(const Message& msg, Print& out) {
    using namespace azaraC::def;
    out.print('{');
    wf_u(out, "svid",     msg.svid);
    wf_s(out, "svid_label",
        qzss_dcr_satellite_prn_lookup(msg.svid));
    wf_u(out, "msg_type", msg.msg_type);
    wf_s(out, "msg_type_label",
        qzss_dcr_message_type_lookup(msg.msg_type));
    wf_x(out, "crc24",    msg.crc24);

#if (AZARAC_ENABLE_DCX_CAMF)
    if (msg.msg_type == 44) {
        serializeDcx(msg, out);
    } else
#endif
    if (msg.msg_type == 43) {
        // Use safe accessor for Mt43Data
        const Mt43Data* d = msg.getMt43();
        if (!d) {
            wf_s(out, keys::note, "invalid_mt43", /*last=*/true);
            out.print('}');
            return;
        }
        
        wf_u(out, "report_classification", d->report_classification);
        wf_s(out, "report_classification_label",
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_report_classification_lookup, qzss_dcr_jma_report_classification_en_lookup, d->report_classification));
        wf_u(out, "disaster_category", d->disaster_category);
        wf_s(out, "disaster_category_label",
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_disaster_category_lookup, qzss_dcr_jma_disaster_category_en_lookup, d->disaster_category));
        wf_u(out, "information_type", d->information_type);
        wf_s(out, "information_type_label",
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_information_type_lookup, qzss_dcr_jma_information_type_en_lookup, d->information_type));
        writeDHM(out, "report_time", d->event_time);
        wk(out, "detail"); out.print('{');

        // Dispatch to enabled serializers based on disaster_category
        // (switch: O(1) dispatch; categories 7/13 are undefined in the spec)
        bool serialized = false;
        switch (d->disaster_category) {
#if (AZARAC_ENABLE_EEW)
        case 1:  serialized = serializeEEW(d, out); break;
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        case 2:  serialized = serializeHypocenter(d, out); break;
#endif
#if (AZARAC_ENABLE_SEISMIC)
        case 3:  serialized = serializeSeismic(d, out); break;
#endif
#if (AZARAC_ENABLE_NANKAI)
        case 4:  serialized = serializeNankai(d, out); break;
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        case 5:  serialized = serializeTsunami(d, out); break;
#endif
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        case 6:  serialized = serializeNwPacTsu(d, out); break;
#endif
#if (AZARAC_ENABLE_VOLCANO)
        case 8:  serialized = serializeVolcano(d, out); break;
#endif
#if (AZARAC_ENABLE_ASH_FALL)
        case 9:  serialized = serializeAshFall(d, out); break;
#endif
#if (AZARAC_ENABLE_WEATHER)
        case 10: serialized = serializeWeather(d, out); break;
#endif
#if (AZARAC_ENABLE_FLOOD)
        case 11: serialized = serializeFlood(d, out); break;
#endif
#if (AZARAC_ENABLE_TYPHOON)
        case 12: serialized = serializeTyphoon(d, out); break;
#endif
#if (AZARAC_ENABLE_MARINE)
        case 14: serialized = serializeMarine(d, out); break;
#endif
        default:
            break;
        }
        if (!serialized) wf_s(out, keys::note, "unsupported_category", /*last=*/true);

        out.print('}');  // detail

    } else {
        wf_s(out, keys::note, "unsupported_msg_type", /*last=*/true);
    }

    out.print('}');
}

} // namespace internal
} // namespace azaraC
