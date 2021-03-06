#ifndef EFFECTIVEFLUXUNCERTAINTYHELPER_SEEN
#define EFFECTIVEFLUXUNCERTAINTYHELPER_SEEN

#include "TH2.h"

#include "fhiclcpp/ParameterSet.h"

#include <limits>
#include <memory>
#include <vector>

class EffectiveFluxUncertaintyHelper {
public:
  static int const kND_numu_numode = 0;
  static int const kND_nue_numode = 1;
  static int const kND_numubar_numode = 2;
  static int const kND_nuebar_numode = 3;

  static int const kND_numu_nubarmode = 4;
  static int const kND_nue_nubarmode = 5;
  static int const kND_numubar_nubarmode = 6;
  static int const kND_nuebar_nubarmode = 7;

  static int const kFD_numu_numode = 8;
  static int const kFD_nue_numode = 9;
  static int const kFD_numubar_numode = 10;
  static int const kFD_nuebar_numode = 11;

  static int const kFD_numu_nubarmode = 12;
  static int const kFD_nue_nubarmode = 13;
  static int const kFD_numubar_nubarmode = 14;
  static int const kFD_nuebar_nubarmode = 15;

  static int const kUnhandled = 16;

  static int const kInvalidBin = std::numeric_limits<int>::max();

private:
  std::vector<std::vector<std::unique_ptr<TH2>>> NDTweaks;
  std::vector<std::vector<std::unique_ptr<TH1>>> FDTweaks;

public:
  void Initialize(fhicl::ParameterSet const &);

  size_t GetNParameters() { return NDTweaks.size(); }

  int GetNuConfig(int nu_pdg, bool IsND = true, bool IsNuMode = true);

  // This form checks that the neutrino is within weighting bin ranges and
  // returns kUnhandled if not
  int GetNuConfig(int nu_pdg, double enu_GeV, double off_axix_pos_m,
                  size_t param_id = 0, bool IsND = true, bool IsNuMode = true);

  int GetBin(int nu_pdg, double enu_GeV, double off_axix_pos_m,
             size_t param_id = 0, bool IsND = true, bool IsNuMode = true);

  // This form does no checking other than for kUnhandled
  double GetFluxWeight(size_t param_id, double param_val, int bin,
                                 int nu_config);

  double GetFluxWeight(size_t param_id, double param_val, double enu_GeV,
                       double off_axix_pos_m, int nu_pdg, bool IsND,
                       bool IsNuMode) {
    return GetFluxWeight(
        param_id, param_val,
        GetBin(nu_pdg, enu_GeV, off_axix_pos_m, param_id, IsND, IsNuMode),
        GetNuConfig(nu_pdg, IsND, IsNuMode));
  }
};

#endif
