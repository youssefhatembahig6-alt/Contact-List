-- ─────────────────────────────────────────────────────────────────────────────
--  Contact Management System — MySQL Schema
--  CSE333 · Spring 2026
--
--  Run this ONCE before launching the app:
--      mysql -u root -p < contacts.sql
-- ─────────────────────────────────────────────────────────────────────────────

CREATE DATABASE IF NOT EXISTS contact_db
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE contact_db;

CREATE TABLE IF NOT EXISTS contacts (
    id         INT          AUTO_INCREMENT PRIMARY KEY,
    name       VARCHAR(100) NOT NULL,
    phone      VARCHAR(20)  NOT NULL UNIQUE,   -- phone must be unique (mirrors AVL logic)
    email      VARCHAR(150)          DEFAULT '',
    address    VARCHAR(255)          DEFAULT '',
    created_at TIMESTAMP             DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP             DEFAULT CURRENT_TIMESTAMP
                                     ON UPDATE CURRENT_TIMESTAMP,

    INDEX idx_name (name)            -- speeds up SELECT / ORDER BY name
);
SELECT * FROM contacts;
