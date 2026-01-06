## 📂 Structure du Projet

L'architecture du projet est divisée en trois modules principaux pour assurer la modularité entre les deux robots.

```bash
.
├── 📚 lib/           # Bibliothèque de classes partagées (Abstractions matérielles & Services partagés)
├── 🤖 app1/          # Code source du Robot 1 (Centrage & Réception IR)
└── 🤖 app2/          # Code source du Robot 2 (Navigation, Cartographie & Transmission IR)
