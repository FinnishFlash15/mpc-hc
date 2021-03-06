﻿/*
 * (C) 2016 see Authors.txt
 *
 * This file is part of MPC-HC.
 *
 * MPC-HC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-HC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "SubtitlesProviders.h"
#include "VersionInfo.h"

#include "XmlRpc4Win/TimXmlRpc.h"

#define DEFINE_SUBTITLESPROVIDER_BEGIN(P, U, I, F)                                     \
class P final : public SubtitlesProvider {                                             \
public:                                                                                \
    P(SubtitlesProviders* pOwner)                                                      \
        : SubtitlesProvider(pOwner) {                                                  \
        Initialize();                                                                  \
    }                                                                                  \
    ~P() { Uninitialize(); }                                                           \
    P(P const&) = delete;                                                              \
    P& operator=(P const&) = delete;                                                   \
    static std::shared_ptr<P> Create(SubtitlesProviders* pOwner) {                     \
        return std::make_shared<P>(pOwner);                                            \
    }                                                                                  \
private:                                                                               \
    virtual std::string Name() const override { return #P; }                           \
    virtual std::string Url() const override { return U; }                             \
    virtual const std::set<std::string>& Languages() const override;                   \
    virtual bool Flags(DWORD dwFlags) const override { return (dwFlags & (F)) == dwFlags; }  \
    virtual int Icon() const override { return I; }                                    \
private:                                                                               \
    virtual SRESULT Search(const SubtitlesInfo& pFileInfo) override;                   \
    virtual SRESULT Download(SubtitlesInfo& pSubtitlesInfo) override;
#define DEFINE_SUBTITLESPROVIDER_END                                                   \
};

DEFINE_SUBTITLESPROVIDER_BEGIN(OpenSubtitles, "http://www.opensubtitles.org", IDI_OPENSUBTITLES, SPF_LOGIN | SPF_HASH | SPF_UPLOAD)
void Initialize() override;
bool NeedLogin() override;
SRESULT Login(const std::string& sUserName, const std::string& sPassword) override;
SRESULT LogOut() override;
SRESULT Hash(SubtitlesInfo& pFileInfo) override;
SRESULT Upload(const SubtitlesInfo& pSubtitlesInfo) override;
std::unique_ptr<XmlRpcClient> xmlrpc;
XmlRpcValue token;
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(SubDB, "http://api.thesubdb.com", IDI_SUBDB, SPF_HASH | SPF_UPLOAD)
SRESULT Hash(SubtitlesInfo& pFileInfo) override;
SRESULT Upload(const SubtitlesInfo& pSubtitlesInfo) override;
std::string UserAgent() const override
{
    return SubtitlesProvidersUtils::StringFormat("SubDB/1.0 (MPC-HC/%s; http://mpc-hc.org)",
                                                 VersionInfo::GetVersionString());
}
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(podnapisi, "https://www.podnapisi.net", IDI_PODNAPISI, SPF_SEARCH)
SRESULT Login(const std::string& sUserName, const std::string& sPassword) override;
SRESULT Hash(SubtitlesInfo& pFileInfo) override;
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(titlovi, "http://www.titlovi.com", IDI_TITLOVI, SPF_SEARCH)
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(ysubs, "http://www.yifysubtitles.com", IDI_YSUBS, SPF_SEARCH)
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(Napisy24, "http://napisy24.pl/", IDI_N24, SPF_HASH | SPF_SEARCH)
SRESULT Hash(SubtitlesInfo& pFileInfo) override;
DEFINE_SUBTITLESPROVIDER_END

static const struct {
    const char* code;
    const char* name;
} podnapisi_languages[] = {
    { /* 0*/ "",   "" },                        { /* 1*/ "sl", "Slovenian" },              { /* 2*/ "en", "English" },
    { /* 3*/ "no", "Norwegian" },               { /* 4*/ "ko", "Korean" },                 { /* 5*/ "de", "German" },
    { /* 6*/ "is", "Icelandic" },               { /* 7*/ "cs", "Czech" },                  { /* 8*/ "fr", "French" },
    { /* 9*/ "it", "Italian" },                 { /*10*/ "bs", "Bosnian" },                { /*11*/ "ja", "Japanese" },
    { /*12*/ "ar", "Arabic" },                  { /*13*/ "ro", "Romanian" },               { /*14*/ "es", "Argentino" },
    { /*15*/ "hu", "Hungarian" },               { /*16*/ "el", "Greek" },                  { /*17*/ "zh", "Chinese" },
    { /*18*/ "",   "" },                        { /*19*/ "lt", "Lithuanian" },             { /*20*/ "et", "Estonian" },
    { /*21*/ "lv", "Latvian" },                 { /*22*/ "he", "Hebrew" },                 { /*23*/ "nl", "Dutch" },
    { /*24*/ "da", "Danish" },                  { /*25*/ "sv", "Swedish" },                { /*26*/ "pl", "Polish" },
    { /*27*/ "ru", "Russian" },                 { /*28*/ "es", "Spanish" },                { /*29*/ "sq", "Albanian" },
    { /*30*/ "tr", "Turkish" },                 { /*31*/ "fi", "Finnish" },                { /*32*/ "pt", "Portuguese" },
    { /*33*/ "bg", "Bulgarian" },               { /*34*/ "",   "" },                       { /*35*/ "mk", "Macedonian" },
    { /*36*/ "sr", "Serbian" },                 { /*37*/ "sk", "Slovak" },                 { /*38*/ "hr", "Croatian" },
    { /*39*/ "",   "" },                        { /*40*/ "zh", "Mandarin" },               { /*41*/ "",   "" },
    { /*42*/ "hi", "Hindi" },                   { /*43*/ "",   "" },                       { /*44*/ "th", "Thai" },
    { /*45*/ "",   "" },                        { /*46*/ "uk", "Ukrainian" },              { /*47*/ "sr", "Serbian (Cyrillic)" },
    { /*48*/ "pb", "Brazilian" },               { /*49*/ "ga", "Irish" },                  { /*50*/ "be", "Belarus" },
    { /*51*/ "vi", "Vietnamese" },              { /*52*/ "fa", "Farsi" },                  { /*53*/ "ca", "Catalan" },
    { /*54*/ "id", "Indonesian" },              { /*55*/ "ms", "Malay" },                  { /*56*/ "si", "Sinhala" },
    { /*57*/ "kl", "Greenlandic" },             { /*58*/ "kk", "Kazakh" },                 { /*59*/ "bn", "Bengali" },
};

static const struct {
    const char* code;
    const char* name;
} titlovi_languages[] = {
    { "hr", "hr" }, { "sr", "sr" }, { "rs", "sr" }, { "si", "sl" }, { "ba", "bs" }, { "en", "en" }, { "mk", "mk" },
};

static const struct {
    const char* code;
    const char* name;
} ysubs_languages[] = {
    { "sq", "albanian" },                       { "ar", "arabic" },                        { "bn", "bengali" },
    { "pb", "brazilian-portuguese" },           { "bg", "bulgarian" },                     { "zh", "chinese" },
    { "hr", "croatian" },                       { "cs", "czech" },                         { "da", "danish" },
    { "nl", "dutch" },                          { "en", "english" },                       { "fa", "farsi-persian" },
    { "fi", "finnish" },                        { "fr", "french" },                        { "de", "german" },
    { "el", "greek" },                          { "he", "hebrew" },                        { "hu", "hungarian" },
    { "id", "indonesian" },                     { "it", "italian" },                       { "ja", "japanese" },
    { "ko", "korean" },                         { "lt", "lithuanian" },                    { "mk", "macedonian" },
    { "ms", "malay" },                          { "no", "norwegian" },                     { "pl", "polish" },
    { "pt", "portuguese" },                     { "ro", "romanian" },                      { "ru", "russian" },
    { "sr", "serbian" },                        { "sl", "slovenian" },                     { "es", "spanish" },
    { "sv", "swedish" },                        { "th", "thai" },                          { "tr", "turkish" },
    { "ur", "urdu" },                           { "vi", "vietnamese" },
};

DEFINE_SUBTITLESPROVIDER_BEGIN(TVsubtitles, "http://www.tvsubtitles.net", IDI_TVSUBTITLES, SPF_SEARCH)
static const std::regex regex_pattern[];
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(Moviesubtitles, "http://www.moviesubtitles.org", IDI_MOVIESUBTITLES, SPF_SEARCH)
static const std::regex regex_pattern[];
DEFINE_SUBTITLESPROVIDER_END

DEFINE_SUBTITLESPROVIDER_BEGIN(addic7ed, "http://www.addic7ed.com", IDI_ADDIC7ED, SPF_LOGIN)
virtual SRESULT Login(const std::string& sUserName, const std::string& sPassword);
std::string UserAgent() const override;
std::string GetLanguagesString();
static const std::regex regex_pattern[];
DEFINE_SUBTITLESPROVIDER_END


static const struct { const char* code; const char* name; } addic7ed_languages[] = {
    { /* 0*/ "", "" },                          { /* 1*/ "en", "English" },                { /* 2*/ "", "" },
    { /* 3*/ "", "" },                          { /* 4*/ "es", "Spanish" },                { /* 5*/ "es", "Spanish (Spain)" },
    { /* 6*/ "es", "Spanish (Latin America)" }, { /* 7*/ "it", "Italian" },                { /* 8*/ "fr", "French" },
    { /* 9*/ "pt", "Portuguese" },              { /*10*/ "pb", "Portuguese (Brazilian)" }, { /*11*/ "de", "German" },
    { /*12*/ "ca", UTF16To8(_T("Català")) },    { /*13*/ "eu", "Euskera" },                { /*14*/ "cs", "Czech" },
    { /*15*/ "gl", "Galego" },                  { /*16*/ "tr", "Turkish" },                { /*17*/ "nl", "Dutch" },
    { /*18*/ "sv", "Swedish" },                 { /*19*/ "ru", "Russian" },                { /*20*/ "hu", "Hungarian" },
    { /*21*/ "pl", "Polish" },                  { /*22*/ "sl", "Slovenian" },              { /*23*/ "he", "Hebrew" },
    { /*24*/ "zh", "Chinese (Traditional)" },   { /*25*/ "sk", "Slovak" },                 { /*26*/ "ro", "Romanian" },
    { /*27*/ "el", "Greek" },                   { /*28*/ "fi", "Finnish" },                { /*29*/ "no", "Norwegian" },
    { /*30*/ "da", "Danish" },                  { /*31*/ "hr", "Croatian" },               { /*32*/ "ja", "Japanese" },
    { /*33*/ "", "" },                          { /*34*/ "", "" },                         { /*35*/ "bg", "Bulgarian" },
    { /*36*/ "sr", "Serbian (Latin)" },         { /*37*/ "id", "Indonesian" },             { /*38*/ "ar", "Arabic" },
    { /*39*/ "sr", "Serbian (Cyrillic)" },      { /*40*/ "ms", "Malay" },                  { /*41*/ "zh", "Chinese (Simplified)" },
    { /*42*/ "ko", "Korean" },                  { /*43*/ "fa", "Persian" },                { /*44*/ "bs", "Bosnian" },
    { /*45*/ "vi", "Vietnamese" },              { /*46*/ "th", "Thai" },                   { /*47*/ "bn", "Bengali" },
    { /*48*/ "az", "Azerbaijani" },             { /*49*/ "mk", "Macedonian" },             { /*50*/ "hy", "Armenian" },
    { /*51*/ "uk", "Ukrainian" },               { /*52*/ "sq", "Albanian" },
};

static const struct { const char* code; const char* name; } tvsubtitles_languages[] = {
    { "br", "pb" }, { "ua", "uk" }, { "gr", "el" }, { "cn", "zh" }, { "jp", "ja" }, { "cz", "cs" },
};

static const struct { const char* code; const char* name; } moviesubtitles_languages[] = {
    { "br", "pb" }, { "ua", "uk" }, { "gr", "el" }, { "cn", "zh" }, { "jp", "ja" }, { "cz", "cs" },
};
