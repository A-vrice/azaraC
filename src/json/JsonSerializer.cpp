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

// Top-level serialize entry: dispatch by msg_type
void JsonSerializer::serialize(const Message& msg, Print& out) {
    using namespace azaraC::def;
    out.print('{');
    wf_u(out, "svid",     msg.svid);
    // IS-QZSS-DCR-017 §4.3.1: "Satellite ID is 6 LSB of the 8 bit which
    // represented PRN of the L1S". The framers normalise svid to PRN
    // (NmeaFramer adds 128, UbxFramer maps through svid_prn), so mask back to
    // the 6 LSB the table is keyed by (55/56/57/58/61).
    wf_s(out, "svid_label",
        qzss_dcr_satellite_prn_lookup(msg.svid & 0x3F));
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
        const Mt43Data* d = msg.getMt43();
        if (!d) {
            wf_s(out, keys::note, "invalid_mt43", /*last=*/true);
            out.print('}');
            return;
        }
        
        wf_u(out, "report_classification", d->report_classification);
        AZARAC_LABEL(out, "report_classification_label",
            qzss_dcr_jma_report_classification_lookup,
            qzss_dcr_jma_report_classification_en_lookup, d->report_classification, false);
        wf_u(out, "disaster_category", d->disaster_category);
        AZARAC_LABEL(out, "disaster_category_label",
            qzss_dcr_jma_disaster_category_lookup,
            qzss_dcr_jma_disaster_category_en_lookup, d->disaster_category, false);
        wf_u(out, "information_type", d->information_type);
        AZARAC_LABEL(out, "information_type_label",
            qzss_dcr_jma_information_type_lookup,
            qzss_dcr_jma_information_type_en_lookup, d->information_type, false);
        // Vn は仕様上 1 以外を decodeQzqsm が拒否するため、ここでは常に 1。
        // 「値が無い」と「1 だった」を区別できるよう明示する。
        wf_u(out, "version", d->version);
        writeDHM(out, "report_time", d->event_time);
        wk(out, "detail"); out.print('{');

        // Dispatch by disaster_category (categories 7/13 undefined in spec)
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

        out.print('}');

    } else {
        wf_s(out, keys::note, "unsupported_msg_type", /*last=*/true);
    }

    out.print('}');
}

} // namespace internal
} // namespace azaraC
