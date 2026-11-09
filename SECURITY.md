# Security & Confidential Architecture Policy

## 1. Private Vulnerability & Architecture Reporting

We take the security, architectural integrity, and clean-room provenance of **PrismX** with the utmost seriousness.

If you have discovered a potential security vulnerability, memory corruption defect, shader runtime flaw, or if you are a graphics architect wishing to discuss confidential technical questions regarding clean-room Direct3D 12 / Vulkan ABI specifications:

👉 **Please submit a private report via GitHub's Private Vulnerability Reporting channel:**  
**[Report a Vulnerability / Confidential Advisory](https://github.com/MicaNT-Kernel/PrismX/security/advisories/new)**

### What Happens When You Submit a Private Report:
- **100% Confidential**: Private advisories are visible **only** to the repository maintainers and the reporter.
- **Zero Public Activity**: Submitting a private advisory does **not** create a public issue, does **not** generate public GitHub timeline activity, and will **not** appear on your public GitHub profile or corporate feed.
- **Chatham House Rule**: We welcome discrete, off-the-record inquiries from industry engineers, graphics architects, driver developers, and hardware vendor specialists under strict confidentiality.

---

## 2. Direct Confidential Contact

If you prefer out-of-band communication or encrypted correspondence:
- **Primary Contact**: Daniel Elliott
- **Email**: `daniel@micant.org` (or `security@micant.org`)
- **PGP / Encrypted Inquiries**: Available upon request for confidential vendor and platform interoperability discussions.

---

## 3. Scope & Supported Versions

| Version / Branch | Supported | Notes |
| :--- | :--- | :--- |
| `main` (Milestone releases) | :white_check_mark: | Active C++23 Direct3D 12 Agility SDK & Vulkan development |
| Prior release tags | :white_check_mark: | Critical CVE / GPU fault patches backported |

---

## 4. Response Timeline & Disclosure Process

- **Initial Acknowledgment**: Within 24–48 hours of receipt.
- **Remediation & Patching**: Rapid cycle integration into the next Milestone suite.
- **Coordinated Disclosure**: We collaborate with reporters on mutually agreed disclosure schedules, attribution (or anonymous handling if preferred by the reporter).
