# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 1.x     | :white_check_mark: |

## Reporting a Vulnerability

**Developed for safety-critical applications (disaster warning systems).**
Responsible disclosure protects all users of this library.

If you discover a security vulnerability:

1. **Do NOT open a public issue.**
2. Email [avrice@proton.me](mailto:avrice@proton.me) with:
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact assessment
3. You will receive an initial response within 72 hours.
4. We will work with you to understand and address the issue before any public disclosure.

## Security Advisories

Critical vulnerabilities will be published as [GitHub Security Advisories](https://github.com/A-vrice/azaraC/security/advisories).

## Dependency Management

We use [Renovate](https://docs.renovatebot.com/) to keep dependencies up to date.
All dependency updates are reviewed and merged only after passing CI tests.

## Code Integrity

- All releases include [SLSA Level 3](https://slsa.dev/) provenance attestations
- Build artifacts are signed via GitHub Artifact Attestations
- Source archives are verified before release creation

## Scope

This security policy covers the azaraC library code distributed via GitHub Releases.
It does not cover:
- Third-party libraries or dependencies
- Hardware implementations using this library
- Applications built with this library
